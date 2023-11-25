# VL53L1X-STM32

Copiato qui funzioni e parte del main per un progetto con STM32CubeMonitor che mostra i valori letti dal TOF


in main.c 

...
  /* USER CODE BEGIN WHILE */

  if (VL53L1__Init()) {
	  while (1) {
		  for (uint8_t k=0;k<4;k++) {
			  HAL_GPIO_TogglePin(USER_LED_GPIO_Port, USER_LED_Pin);
			  HAL_Delay(100);
		  }
		  HAL_Delay(400);
	  };
  }
  VL53L1X_StartRanging(TOF_ADDR);   /* Enabling ranging */

  while (1)
  {
	  __NOP();
	  VL53L1__test();
....