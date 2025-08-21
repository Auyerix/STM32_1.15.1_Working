/*
 * Copyright (c) 2023 Juan Manuel Cruz <jcruz@fi.uba.ar>.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from
 *    this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 *
 * @file   : task_test.c
 * @date   : Set 26, 2023
 * @author : Juan Manuel Cruz <jcruz@fi.uba.ar> <jcruz@frba.utn.edu.ar>
 * @version	v1.0.0
 */

/********************** inclusions *******************************************/
/* Project includes. */
#include "main.h"
#include "cmsis_os.h"

/* Demo includes. */
#include "logger.h"
#include "dwt.h"

/* Application & Tasks includes. */
#include "board.h"
#include "app.h"

/********************** macros and definitions *******************************/
#define G_TASK_TEST_CNT_INI		0u

#define TASK_TEST_TICK_DEL_MAX	5000

/********************** internal data declaration ****************************/
/* Events to excite tasks */
typedef enum e_task_test {Error, Entry_A, Entry_B, Exit_A, Exit_B} e_task_test_t;

/********************** internal functions declaration ***********************/

/********************** internal data definition *****************************/
const char *p_task_test						= "Periodically excites other tasks";
const char *p_task_test_priority			= "  <=> Task Test - Priority:";
const char *p_task_test_e_task_test_array	= "  <=> Task Test - e_task_test_array:";

const char *p_task_test_signal_entry_a		= "  <=> Task Test - Signal: Entry_A  <=>";
const char *p_task_test_signal_exit_a		= "  <=> Task Test - Signal: Exit_A   <=>";
const char *p_task_test_signal_entry_b		= "  <=> Task Test - Signal: Entry_B  <=>";
const char *p_task_test_signal_exit_b		= "  <=> Task Test - Signal: Exit_B   <=>";
const char *p_task_test_signal_error  		= "  <=> Task Test - Signal: Error    <=>";

const char *p_task_test_wait_5000mS			= "  <=> Task Test - Wait:   5000mS";

#define E_TASK_TEST_X (1)

#if (E_TASK_TEST_X == 0)
/* Array of events to excite tasks */
const e_task_test_t e_task_test_array[] = {Error, Exit_B+1, Exit_B+2};
#endif

#if (E_TASK_TEST_X == 1)
/* Array of events to excite tasks */
const e_task_test_t e_task_test_array[] = {Entry_A, Exit_A, Entry_A, Exit_A};
#endif

#if (E_TASK_TEST_X == 2)
/* Array of events to excite tasks */
const e_task_test_t e_task_test_array[] = {Entry_A, Entry_A, Exit_A, Exit_A};
#endif

#if (E_TASK_TEST_X == 3)
/* Array of events to excite tasks */
const e_task_test_t e_task_test_array[] = {Entry_B, Exit_B, Entry_B, Exit_B};
#endif

#if (E_TASK_TEST_X == 4)
/* Array of events to excite tasks */
const e_task_test_t e_task_test_array[] = {Entry_B, Entry_B, Exit_B, Exit_B};
#endif

#if (E_TASK_TEST_X == 5)
/* Array of events to excite tasks */
const e_task_test_t e_task_test_array[] = {Entry_A, Exit_A, Entry_B, Exit_B};
#endif

#if (E_TASK_TEST_X == 6)
/* Array of events to excite tasks */
const e_task_test_t e_task_test_array[] = {Entry_B, Exit_B, Entry_A, Exit_A};
#endif

#if (E_TASK_TEST_X == 7)
/* Array of events to excite tasks */
const e_task_test_t e_task_test_array[] = {Entry_A, Entry_B, Exit_A, Exit_B};
#endif

#if (E_TASK_TEST_X == 8)
/* Array of events to excite tasks */
const e_task_test_t e_task_test_array[] = {Entry_B, Entry_A, Exit_B, Exit_A};
#endif

/********************** external data declaration *****************************/
uint32_t g_task_test_cnt;

/********************** external functions definition ************************/
/* Task Test thread */
void task_test(void *parameters)
{
	#if (TEST_X == TEST_0)

	g_task_test_cnt = G_TASK_TEST_CNT_INI;

	/*  Declare & Initialize Task Function variables for argument, led, button and task */
	TickType_t last_wake_time;

	/* The xLastWakeTime variable needs to be initialized with the current tick
	   count. ws*/
	last_wake_time = xTaskGetTickCount();

	char *p_task_name = (char *) pcTaskGetName(NULL);

	/* Print out: Application Update */
	LOGGER_LOG("  %s is running - %s\r\n", p_task_name, p_task_test);

	/* This task will run the first time after other tasks as it has the lower
	 * priority.
	 *
	 * Query the priority at which this task is running - passing in NULL means
	 * "return our own priority". */
	UBaseType_t task_test_priority;
	task_test_priority = uxTaskPriorityGet(NULL) + 2UL;

	/* Setting the TestingTask priority above the other tasks priority will
	 * cause TestingTask to immediately start running (as then TestingTask
	 * will have the higher priority of the three created tasks). */
	vTaskPrioritySet(NULL, task_test_priority);

	/* Print out: Task priority */
	LOGGER_LOG("  %s %s %d\r\n", p_task_test_priority, GET_NAME(task_test_priority), (int)task_test_priority);

	#endif

	#if (TEST_X == TEST_1)

	/* Here another code option */

	#endif

	#if (TEST_X == TEST_2)

	/* Here Chatbot Artificial Intelligence generated code */

	#endif

	/* As per most tasks, this task is implemented in an infinite loop. */
	for (;;)
	{

		#if (TEST_X == TEST_0)

		uint32_t index = E_TASK_TEST_X;

		/* Scanning the array of events to excite tasks */
		for (index = 0; index < (sizeof(e_task_test_array)/sizeof(e_task_test_t)); index++)
		{
			/* Update Task Task Counter */
			g_task_test_cnt++;

			/* Print out: Event Task Test Array Index */
			LOGGER_LOG("  %s %s %d\r\n", p_task_test_e_task_test_array, GET_NAME(index), (int)index);

			switch (e_task_test_array[index]) {

	    		case Entry_A:

		    		/* Print out: Signal Entry A */
		    		LOGGER_LOG("  %s\r\n", p_task_test_signal_entry_a);
		    		xSemaphoreGive(binary_semaphore_entry_a_h);
		    		break;

	    		case Exit_A:

		    		/* Print out: Signal Exit A */
		    		LOGGER_LOG("  %s\r\n", p_task_test_signal_exit_a);
		    		xSemaphoreGive(binary_semaphore_exit_a_h);
		    		break;

	    		case Entry_B:

		    		/* Print out: Signal Entry B */
		    		LOGGER_LOG("  %s\r\n", p_task_test_signal_entry_b);
		    		xSemaphoreGive(binary_semaphore_entry_b_h);
		    		break;
		    		
		    		case Exit_B:

		    		/* Print out: Signal Exit B */
		    		LOGGER_LOG("  %s\r\n", p_task_test_signal_exit_b);
		    		xSemaphoreGive(binary_semaphore_exit_b_h);
		    		break;

		    	case Error:
		    	default:

		    		/* Print out: Signal Error */
		    		LOGGER_LOG("  %s\r\n", p_task_test_signal_error);
		    		break;
		    }

			/* Print out: Wait 5000mS */
//			LOGGER_LOG("  %s - %s %d\r\n", p_task_test_wait_5000mS, GET_NAME(g_task_test_cnt), (int)g_task_test_cnt);
			LOGGER_LOG("  %s\r\n", p_task_test_wait_5000mS);

			/* We want this task to execute exactly every 5000 milliseconds. */
			vTaskDelayUntil(&last_wake_time, TASK_TEST_TICK_DEL_MAX);
		}

		#endif

		#if (TEST_X == TEST_1)

		/* Here another code option */

		#endif

		#if (TEST_X == TEST_2)

		/* Here Chatbot Artificial Intelligence generated code */

		#endif
	}
}

/********************** end of file ******************************************/
