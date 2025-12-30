#ifndef __GPIO_H__
#define __GPIO_H__


#include <common.h>

#define GPIOC_BASEADDR          0x40011000
#define GPIOC_CRL_OFFSET        0x00
#define GPIOC_CRH_OFFSET        0x04
#define GPIOC_IDR_OFFSET        0x08
#define GPIOC_ODR_OFFSET        0x0C
#define GPIOC_BSRR_OFFSET       0x10
#define GPIOC_BRR_OFFSET        0x14
#define GPIOC_LCKR_OFFSET       0x18

#define GPIOx_CRL_RESET     0x44444444
#define GPIOx_CRH_RESET     0x44444444
#define GPIOx_IDR_RESET     0x00000000
#define GPIOx_ODR_RESET     0x00000000
#define GPIOx_BSRR_RESET    0x00000000
#define GPIOx_BRR_RESET     0x00000000
#define GPIOx_LCKR_RESET    0x00000000

#define CNF_GPO_PP          0b00
#define CNF_GPO_OD          0b01
#define CNF_AFO_PP          0b10
#define CNF_AFO_OD          0b11

#define MODE_INPUT          0b00
#define MODE_OUTPUT_10MHz   0b01
#define MODE_OUTPUT_2MHz    0b10
#define MODE_OUTPUT_50MHz   0b11

typedef struct {
    volatile uint32_t crl;
    volatile uint32_t crh;
    volatile uint32_t idr;
    volatile uint32_t odr;
    volatile uint32_t bsrr;
    volatile uint32_t brr;
    volatile uint32_t lckr;
} __align(1) gpio_regs_t;

int32_t gpio_init(gpio_regs_t *dev, const uint32_t baseaddr);
uint32_t conf_cr_port(const uint8_t cnf, const uint8_t mode, const uint8_t port);
void configure_gpio_all_output(gpio_regs_t *dev);
void set_gpio_output(gpio_regs_t *dev, uint32_t vals);


#endif /* __GPIO_H__ */
