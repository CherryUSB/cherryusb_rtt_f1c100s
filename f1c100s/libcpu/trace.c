#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rtthread.h"
#include "rtdef.h"

#if 0
static rt_bool disassembly_ins_is_bl_blx(uint32_t addr)
{
    uint16_t ins1 = *((uint16_t *)addr);
    uint16_t ins2 = *((uint16_t *)(addr + 2));

#define BL_INS_MASK 0xF800
#define BL_INS_HIGH 0xF800
#define BL_INS_LOW 0xF000
#define BLX_INX_MASK 0xFF00
#define BLX_INX 0x4700

    if ((ins2 & BL_INS_MASK) == BL_INS_HIGH && (ins1 & BL_INS_MASK) == BL_INS_LOW)
    {
        rt_kprintf("BL CMD\n");
        return RT_TRUE;
    }
    else if ((ins2 & BLX_INX_MASK) == BLX_INX)
    {
        rt_kprintf("BLX CMD\n");
        return RT_TRUE;
    }
    else
    {
        return RT_FALSE;
    }
}
#endif

#define STACK_BUF_SIZE (8 * 1024)
ALIGN(4)
static uint32_t call_stack_buf[STACK_BUF_SIZE] = {0};

void rt_hw_stack_trace(rt_thread_t thread)
{
    extern char __text_start;
    extern char __text_end;

    uint32_t code_start_addr;
    uint32_t code_end_addr;
    uint32_t stack_start_addr;
    uint32_t stack_end_addr;
    uint32_t sp;
    uint32_t pc;
    int call_stack_index = 0;

    /* TODO: it should be more portable to calculate code space, like _stext _etext */
    code_start_addr = (uint32_t)(&__text_start);
    code_end_addr = (uint32_t)(&__text_end);

    if (NULL == thread)
    {
        thread = rt_thread_self();
    }

    stack_start_addr = (uint32_t)thread->stack_addr;
    stack_end_addr = thread->stack_size + stack_start_addr;
    sp = (uint32_t)thread->sp;
    rt_kprintf("task=%.8s,stack=[0x%x,0x%x],sp=0x%x,stackoverflow=%d\n", thread->name, stack_start_addr, stack_end_addr, sp, sp < stack_start_addr);
    rt_kprintf("code_start_addr : %lx, code_end_addr : %lx\n", code_start_addr, code_end_addr);
    rt_kprintf("stack buf size : %d\n", STACK_BUF_SIZE);
    for (; sp < stack_end_addr; sp += sizeof(size_t))
    {
        pc = *((uint32_t *)sp);
        // rt_kprintf("pc : %lx\n", pc);
        /* ARM9 using thumb instruction, so the pc must be an odd number */
        // if ((pc & 1) != 0)
        // {
        //     continue;
        // }

        // && disassembly_ins_is_bl_blx(pc - sizeof(size_t))
        if ((code_start_addr < pc) && (pc < code_end_addr))
        {
            call_stack_buf[call_stack_index] = pc;
            call_stack_index++;
            if (call_stack_index >= STACK_BUF_SIZE)
            {
                break;
            }
        }
    }
    if (call_stack_index > 0)
    {
        int index;
        rt_kprintf("arm-none-eabi-addr2line.exe -e rtthread.elf -a -f");
        for (index = 0; index < call_stack_index; index++)
        {
            rt_kprintf(" %lx", call_stack_buf[index]);
        }
        rt_kprintf("\n");
    }
}

RT_WEAK void assert_hook(const char *ex, const char *func, rt_size_t line)
{
    volatile uint8_t _continue = 1;

    rt_enter_critical();

#ifdef RT_USING_FINSH
    // extern long list_thread(void);
    // list_thread();
#endif
    rt_kprintf("%s:%s %s %d\n", __FUNCTION__, ex, func, line);
    rt_hw_stack_trace(RT_NULL);

    while (_continue == 1)
    {
        rt_thread_delay(1000);
        rt_kprintf("assert hook\n");
        //refresh watchdog
    }
}

static int rt_hw_trace_init(void)
{
    rt_assert_set_hook(assert_hook);
    return 0;
}
INIT_APP_EXPORT(rt_hw_trace_init);

void rt_stack_print(int argc, char **argv)
{
    struct rt_object_information *info;
    struct rt_thread *thread;
    struct rt_list_node *node;
    size_t length;

    if (argc < 2)
    {
        rt_kprintf("usage: stack task_name|all_tasks\n");
        rt_hw_stack_trace(NULL);
        return;
    }

    info = rt_object_get_information(RT_Object_Class_Thread);
    if (NULL == info)
    {
        rt_kprintf("can't find thread list\n");
        return;
    }

    length = strlen((const char *)argv[1]);
    if (length <= 0)
    {
        rt_kprintf("bad thread name\n");
        return;
    }
    if ((length == strlen("all_tasks")) && (0 == strncmp(argv[1], "all_tasks", length)))
    {
        for (node = info->object_list.next; node != &info->object_list; node = node->next)
        {
            thread = rt_list_entry(node, struct rt_thread, list);
            rt_hw_stack_trace(thread);
        }
        return;
    }
    if (length > RT_NAME_MAX)
    {
        length = RT_NAME_MAX;
    }

    for (node = info->object_list.next; node != &info->object_list; node = node->next)
    {
        thread = rt_list_entry(node, struct rt_thread, list);
        if (0 != strncmp(argv[1], thread->name, length))
        {
            continue;
        }
        rt_hw_stack_trace(thread);
        break;
    }
}
MSH_CMD_EXPORT_ALIAS(rt_stack_print, stack, rt_hw_stack_trace);

static void assert_test(void)
{
    // RT_ASSERT(0);
    ((void (*)(void))(0xFFF00000))();

    return;
}

void trace_test(void)
{
    assert_test();
}
MSH_CMD_EXPORT(trace_test, trace_test);
