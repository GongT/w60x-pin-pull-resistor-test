#define DBG_SECTION_NAME "main.c"
#include "app.h"
#include <rt-thread-w60x/pins.h>

#define NELEMS(x) (sizeof(x) / sizeof((x)[0]))

static const int pin_nums[] = {
	PIN_NUM_A00,
	PIN_NUM_A01,
	// PIN_NUM_A04,
	// PIN_NUM_A05,
	PIN_NUM_B13,
	PIN_NUM_B14,
	PIN_NUM_B15,
	PIN_NUM_B16,
	PIN_NUM_B17,
	PIN_NUM_B18,
	PIN_NUM_B06,
	PIN_NUM_B07,
	PIN_NUM_B08,
	PIN_NUM_B09,
	PIN_NUM_B10,
	PIN_NUM_B11,
	PIN_NUM_B12,
};

static const char names[NELEMS(pin_nums)][10] = {
	"PA_00",
	"PA_01",
	// "PA_04",
	// "PA_05",
	"PB_13",
	"PB_14",
	"PB_15",
	"PB_16",
	"PB_17",
	"PB_18",
	"PB_06",
	"PB_07",
	"PB_08",
	"PB_09",
	"PB_10",
	"PB_11",
	"PB_12",
};

static int pin_read_conter[NELEMS(pin_nums)];

int main(void)
{
	LOG_I("hello, this is main.");

	rt_memset(pin_read_conter, 0, NELEMS(pin_read_conter));

	for (int index = 0; index < NELEMS(pin_nums); index++)
	{
		rt_kprintf("pin %d (%s) mode pullup\r", index, names[index]);
		rt_pin_mode(index, PIN_MODE_INPUT_PULLUP);
	}
	rt_kprintf("\n");
	rt_thread_mdelay(1000);

	for (int tries = 0; tries < 10; tries++)
	{
		rt_kprintf("read pass %d\n", tries);
		for (int index = 0; index < NELEMS(pin_nums); index++)
		{
			int v = rt_pin_read(pin_nums[index]);
			rt_kprintf("pin %d read value is %d\r", pin_nums[index], v);
			pin_read_conter[index] += v;
		}
		rt_kprintf("\n");
		rt_thread_mdelay(100);
	}

	rt_kprintf("\n");
	rt_kprintf("\n");

	for (int index = 0; index < NELEMS(pin_nums); index++)
	{
		LOG_I("%d: %s = %d", index, names[index], pin_read_conter[index]);
	}

	rt_kprintf("\n");
	rt_kprintf("\n");

	return 0;
}
