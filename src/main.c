#include <common.h>
#include <gpio.h>
#include <rcc.h>

int main(void) {
    mwr((const volatile uint32_t *) (RCC_BASEADDR + RCC_APB2ENR_OFFSET), RCC_APB2ENR_PORTC_EN);

    // gpio_regs_t gpioc;
    // if (gpio_init(&gpioc, GPIOC_BASEADDR)) {
    //     infinite_loop();
    // }

    // configure_gpio_all_output(&gpioc);

    mwr((const volatile uint32_t *) (GPIOC_BASEADDR + GPIOC_CRH_OFFSET), 0x44244444);

    volatile int i;
    while (1) {
        // set_gpio_output(&gpioc, 0xFFFF);
        mwr((const volatile uint32_t *) (GPIOC_BASEADDR + GPIOC_BSRR_OFFSET), 0x2000DFFF);
        i = 2000000;
        while (i) i--;
        // set_gpio_output(&gpioc, 0x0000);
        mwr((const volatile uint32_t *) (GPIOC_BASEADDR + GPIOC_BSRR_OFFSET), 0x0000FFFF);
        i = 2000000;
        while (i) i--;
    }


    infinite_loop();

    return 0;
}
