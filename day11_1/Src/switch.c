/*
 * switch.c
 *
 *  Created on: Apr 5, 2024
 *      Author: chetan
 */

#include "switch.h"

void SwitchInit(uint32_t pin) {
	// enable gpio clock (in AHB1ENR)
	RCC->AHB1ENR |= BV(SWITCH_GPIO_EN);
	// set gpio pin as input (in MODER)
	SWITCH_GPIO->MODER &= ~(BV(pin * 2 + 1) | BV(pin * 2));
	// set gpio pin speed to low (in OSPEEDR)
	SWITCH_GPIO->OSPEEDR &= ~(BV(pin * 2 + 1) | BV(pin * 2));
	// set gpio pin no pull up, no pull down (in PUPDR)
	SWITCH_GPIO->PUPDR &= ~(BV(pin * 2 + 1) | BV(pin * 2));
}

int SwitchGetState(uint32_t pin) {
	// read gpio pin
	uint32_t state = SWITCH_GPIO->IDR;
	// return 1 if pin in high, otherwise return 0
	if(state & BV(pin))
		return 1;
	return 0;
}


// Global flag for interrupt
volatile int exti0_flag = 0;

// Switch EXTT0 IRQ Handler
void EXTI0_IRQHandler(void) {
    // Acknowledge interrupt (in PR)
	EXTI->PR |= BV(SWITCH);
	// Handle interrupt
	exti0_flag = 1;
}












