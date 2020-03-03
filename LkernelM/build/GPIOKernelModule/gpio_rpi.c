
#include <linux/init.h> /* needed by the macros module_init and exit */
#include <linux/module.h> /* needed by all modules */
#include <linux/kernel.h> /* needed by KERN_ definition*/
#include <linux/gpio.h>
#include <linux/interrupt.h>
static unsigned int ledGreen = 4; // GPIO4 (through header pin 7) connected to Green LED
static unsigned int pushButton = 11; // GPIO11 (through pin 23)connects to push Button
static unsigned int irqNumber; // share IRQ num within file
static bool ledOn = 0; // used to toggle state of LED
// The GPIO IRQ Handler function
static irq_handler_t rpi_gpio_isr(unsigned int irq, void *dev_id, struct pt_regs *regs)
{  // toggle the LED state
    // set LED accordingly
    ledOn = !ledOn;                          // Invert the LED state on each button press
    gpio_set_value(ledGreen, ledOn);          // Set the physical LED accordingly
    printk(KERN_ALERT "GPIO Interrupt!\n");
    return (irq_handler_t) IRQ_HANDLED; // announce IRQ handled
}
// The LKM exit function
static void __exit rpi_gpio_exit(void)
{ gpio_set_value(ledGreen, 0); // turn the LED off
    gpio_free(ledGreen); // free the LED GPIO
    gpio_free(pushButton); // free the Button GPIO
    free_irq(irqNumber, NULL); // free the IRQ number, no *dev_id
    printk(KERN_ALERT "Goodbye from the GPIO LKM!\n");
}
// The LKM initialization function
static int __init rpi_gpio_init(void)
{ int result = 0;
    printk(KERN_ALERT " Initializing the GPIO LKM\n");
    ledOn = true; // default for LED is ON
    gpio_request(ledGreen, "sysfs"); // request for LED GPIO
    gpio_direction_output(ledGreen, ledOn); // set in output mode and turn on LED
    gpio_request(pushButton, "sysfs"); // request for push Button GPIO
    gpio_direction_input(pushButton); // set up as input
    gpio_set_debounce(pushButton, 1000); // debounce delay of 1000ms
    irqNumber = gpio_to_irq(pushButton); // map pushbutton to IRQ number
    printk(KERN_ALERT "Button mapped to IRQ: %d\n", irqNumber);
// Requests for an interrupt line
    result = request_irq(irqNumber, // interrupt number requested
                         (irq_handler_t) rpi_gpio_isr, // isr handler function
                         IRQF_TRIGGER_RISING, // trigger on rising edge
                         "rpi_gpio_handler", // used in /proc/interrupts
                         NULL); // *dev_id for shared interrupt lines - NULL
    return result;
}

module_init(rpi_gpio_init);
module_exit(rpi_gpio_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("CE3003");
MODULE_DESCRIPTION("Simple I/O module");
MODULE_VERSION("V1");
