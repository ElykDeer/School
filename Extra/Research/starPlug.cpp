/* Author: Kyle Martin
 * 
 * This code is written at the request of Brendan Dolan-Gavitt
 * 
 * cd /home/hack/
 * 
 * cd /media/sf_School/Extra/Research 
 * run with:
/home/hack/panda/build/i386-softmmu/qemu-system-i386 -replay starcraft4 -display none -panda 'starPlug'
 * 
 */
 
#include <iostream>

#include "panda/plugin.h"
//Need this for EIP?:
//qemu/target-i386/cpu.h

//Needed for panda to detect the sections properly
extern "C"
{
//Pluggin Initialization
bool init_plugin(void *);
//Pluggin Cleanup
void uninit_plugin(void *);
}

//My pluggin:
bool inspect_instruction(CPUState *env, target_ulong pc)
{
    //Get program counter
    uint64_t count = rr_get_guest_instr_count();
	if (count == 0x44c120)
		std::cout << "I guess I'm doing something right!\n";
		
	return false;
}


//Pluggin Initialization
bool init_plugin(void *self)
{
	/*
	//Helps provide and example: 
	  //From scissors, perhaps all we need?
	  //panda_cb pcb = { .before_block_exec = before_block_exec };
	  //panda_register_callback(self, PANDA_CB_BEFORE_BLOCK_EXEC, pcb);
	*/
	//I think I want a good program counter to see if I'm about to execute the line that validates key
	  //void panda_enable_tb_chaining(void); //Not included in stringsearch
	void panda_enable_precise_pc(void);
	
	//I think we'll need this to overwrite the stored key in memory:
	void panda_enable_memcb(void);
	
	//Callback registration:
	
	//So we can inspect each instruction - before an instruction is translated
	panda_cb pcb;
	pcb.insn_translate = inspect_instruction; 
	panda_register_callback(self, PANDA_CB_INSN_TRANSLATE, pcb);
	
	/*//So we can change the code: - before an instruction is executed
	pcb.after_block_exec = PANDA_CB_INSN_EXEC;//
	panda_register_callback(self, PANDA_CB_INSN_EXEC, pcb);*/
	
	return true;
}


void uninit_plugin(void *self)
	{ std::cout << "Done!\n"; }

/*
//Program counter here:
//env->panda_guest_pc

//This is how to chnage memory (CTRL-F the manual):
//int panda_physical_memory_rw(target_phys_addr_t addr, uint8_t *buf, int len, int is_write);
*/

/*
int before_block_exec(CPUState *env, TranslationBlock *tb) {
    //Get program counter
    uint64_t count = rr_get_guest_instr_count();
    
    //Real Program count:
    //count+tb->icount
*/
