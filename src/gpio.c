#include <common.h>
#include <gpio.h>

int32_t gpio_init(gpio_regs_t *dev, const uint32_t baseaddr) {
    if (dev == NULL)
        return -1;

    dev = (gpio_regs_t *) baseaddr;

    dev->crl  = GPIOx_CRL_RESET;
    dev->crh  = GPIOx_CRH_RESET;
    dev->idr  = GPIOx_IDR_RESET;
    dev->odr  = GPIOx_ODR_RESET;
    dev->bsrr = GPIOx_BSRR_RESET;
    dev->brr  = GPIOx_BRR_RESET;
    dev->lckr = GPIOx_LCKR_RESET;

    return 0;
}

uint32_t conf_cr_port(const uint8_t cnf, const uint8_t mode, const uint8_t port) {
    if (port >= 8)
        return 0;
    uint32_t ret = 0;
    ret |= ((cnf & 0x3) << (2 + 4*port));
    ret |= ((mode & 0x3) << (4*port));
    return ret;
}

void configure_gpio_all_output(gpio_regs_t *dev) {
    volatile uint32_t mask = 0;

    mask |= conf_cr_port(CNF_GPO_PP, MODE_OUTPUT_2MHz, 0);
    mask |= conf_cr_port(CNF_GPO_PP, MODE_OUTPUT_2MHz, 1);
    mask |= conf_cr_port(CNF_GPO_PP, MODE_OUTPUT_2MHz, 2);
    mask |= conf_cr_port(CNF_GPO_PP, MODE_OUTPUT_2MHz, 3);
    mask |= conf_cr_port(CNF_GPO_PP, MODE_OUTPUT_2MHz, 4);
    mask |= conf_cr_port(CNF_GPO_PP, MODE_OUTPUT_2MHz, 5);
    mask |= conf_cr_port(CNF_GPO_PP, MODE_OUTPUT_2MHz, 6);
    mask |= conf_cr_port(CNF_GPO_PP, MODE_OUTPUT_2MHz, 7);
    mwr(&dev->crl, mask);
    mask = 0;

    mask |= conf_cr_port(CNF_GPO_PP, MODE_OUTPUT_2MHz, 8-8);
    mask |= conf_cr_port(CNF_GPO_PP, MODE_OUTPUT_2MHz, 9-8);
    mask |= conf_cr_port(CNF_GPO_PP, MODE_OUTPUT_2MHz, 10-8);
    mask |= conf_cr_port(CNF_GPO_PP, MODE_OUTPUT_2MHz, 11-8);
    mask |= conf_cr_port(CNF_GPO_PP, MODE_OUTPUT_2MHz, 12-8);
    mask |= conf_cr_port(CNF_GPO_PP, MODE_OUTPUT_2MHz, 13-8);
    mask |= conf_cr_port(CNF_GPO_PP, MODE_OUTPUT_2MHz, 14-8);
    mask |= conf_cr_port(CNF_GPO_PP, MODE_OUTPUT_2MHz, 15-8);
    mwr(&dev->crh, mask);
}

void set_gpio_output(gpio_regs_t *dev, uint32_t vals) {
    volatile uint32_t bsrr_mask = 0;
    for (uint8_t i = 0; i < 16; i++) {
        if (vals & 0x1) {
            bsrr_mask |= (1 << i);
        } else {
            bsrr_mask |= (1 << (16 + i));
        }
    }
    mwr(&dev->bsrr, bsrr_mask);
}
