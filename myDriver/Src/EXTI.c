#include "EXTI.h"



/**
  * @brief  EXTI_Init for valid GPIO Port and Line Number
  *
  * @param  EXTI_InitStruct = User Config Structure
  *
  * @retval Void
  */

void EXTI_Init(EXTI_InitTypedef_t* EXTI_InitStruct){

	uint32_t tempvalue=0;

	tempvalue= (uint32_t) APB2_EXTI_BASE_ADRR;

	EXTI->IMR1 &= ~(0x1U<<EXTI_InitStruct->EXTI_LineNumber);
	EXTI->EMR1 &= ~(0x1U<<EXTI_InitStruct->EXTI_LineNumber);
	EXTI->IMR2 &= ~(0x1U<<EXTI_InitStruct->EXTI_LineNumber);
	EXTI->EMR2 &= ~(0x1U<<EXTI_InitStruct->EXTI_LineNumber);
	if(EXTI_InitStruct->EXTI_LineCmd != DISABLE){
     tempvalue+=EXTI_InitStruct->EXTI_Mode;


     *((_IO uint32_t*) tempvalue)= (0x1u<<EXTI_InitStruct->EXTI_LineNumber);

     tempvalue= (uint32_t) APB2_EXTI_BASE_ADRR;

     EXTI->RTSR1 &= ~(0X1U<<EXTI_InitStruct->EXTI_LineNumber);
     EXTI->FTSR1 &= ~(0X1U<<EXTI_InitStruct->EXTI_LineNumber);
     if(EXTI_InitStruct->TriggerSelection==EXTI_Trigger_RF){

    	 EXTI->RTSR1 |= (0X1U<<EXTI_InitStruct->EXTI_LineNumber);
    	 EXTI->FTSR1 |= (0X1U<<EXTI_InitStruct->EXTI_LineNumber);

     }
     else{

    	 tempvalue+=EXTI_InitStruct->TriggerSelection;
    	  *((_IO uint32_t*) tempvalue)= (0x1u<<EXTI_InitStruct->EXTI_LineNumber);

     }



	}
	else
	{
		tempvalue= (uint32_t) APB2_EXTI_BASE_ADRR;

	    tempvalue+=EXTI_InitStruct->EXTI_Mode;

		*((_IO uint32_t*) tempvalue) &= ~(0x1u<<EXTI_InitStruct->EXTI_LineNumber);

	}


}


/**
  * @brief  EXTI_LineConfig Configures the pin and port for SYSCFG
  *
  * @param  PortSource = Port Value A-H @def_group Port_Values
  *
  * @param  LineSource = Pin(Line) Numbers @def_group EXTI_Line_Values
  *
  * @retval Void
  */

void EXTI_LineConfig(uint8_t PortSource,uint8_t EXTI_LineSource){

	uint32_t tempval;
	tempval=SYSCFG->EXTICR[EXTI_LineSource>>2U];
	tempval &= ~(0x0F<<(EXTI_LineSource&0x3U)*4);
	tempval= (PortSource<<(EXTI_LineSource&0x3U)*4);
	SYSCFG->EXTICR[EXTI_LineSource>>2U]=tempval;

}


/**
  * @brief  NVIC_EnableInterrupt
  *
  * @param  IRQNumber = IRQNumber of Line
  *
  * @retval Void
  */

void NVIC_EnableInterrupt(uint8_t IRQNumber){

	uint32_t tempvalue=0;
	tempvalue=*((IRQNumber>>5U)+NVIC_ISER0);
	tempvalue &= ~(0X1U<<(IRQNumber&0X1F));
	tempvalue |= (0X1U<<(IRQNumber&0X1F));
	*((IRQNumber>>5U)+NVIC_ISER0)=tempvalue;
}


/**
  * @brief  NVIC_ClearInterrupt
  *
  * @param  IRQNumber = IRQNumber of Line
  *
  * @retval Void
  */

void NVIC_ClearInterrupt(IRQNumber_Typedef_t IRQNumber){

   uint32_t tempvalue=0;
   tempvalue=*((IRQNumber>>5U)+NVIC_ICER0);
   tempvalue &= ~(0X1U<<(IRQNumber&0X1F));
   tempvalue |= (0X1U<<(IRQNumber&0X1F));
   *((IRQNumber>>5U)+NVIC_ICER0)=tempvalue;

}


/**
  * @brief  NVIC_SetPending
  *
  * @param  IRQNumber = IRQNumber of Line
  *
  * @retval Void
  */

void NVIC_SetPending(IRQNumber_Typedef_t IRQNumber){

   uint32_t tempvalue=0;
   tempvalue=*((IRQNumber>>5U)+NVIC_ISPR0);
   tempvalue &= ~(0X1U<<(IRQNumber&0X1F));
   tempvalue |= (0X1U<<(IRQNumber&0X1F));
   *((IRQNumber>>5U)+NVIC_ISPR0)=tempvalue;

}


/**
  * @brief  NVIC_ClearPending
  *
  * @param  IRQNumber = IRQNumber of Line
  *
  * @retval Void
  */

void NVIC_ClearPending(IRQNumber_Typedef_t IRQNumber){

   uint32_t tempvalue=0;
   tempvalue=*((IRQNumber>>5U)+NVIC_ICPR0);
   tempvalue &= ~(0X1U<<(IRQNumber&0X1F));
   tempvalue |= (0X1U<<(IRQNumber&0X1F));
   *((IRQNumber>>5U)+NVIC_ICPR0)=tempvalue;

}


/**
  * @brief  NVIC_SetPriority
  *
  * @param  IRQNumber = IRQNumber of Line
  *
  * @param  priority = Interrupt priority number
  *
  * @retval Void
  */

void NVIC_SetPriority(IRQNumber_Typedef_t IRQNumber, uint8_t priority){

	uint32_t tempvalue=0;
	tempvalue=*((IRQNumber>>2U)+NVIC_IPR0);
	tempvalue &= ~(0xFF<< (8*(IRQNumber>>0x3U)+4) );
	tempvalue |= (priority<<(8*(IRQNumber>>0x3U)+4));
	*((IRQNumber>>2U)+NVIC_IPR0)=tempvalue;

}



