void _irq_handler(uint32_t cause, uint32_t *stack);
uint32_t _exception_handler(uint32_t service, uint32_t value, uint32_t epc, uint32_t opcode);
