################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
usblib/host/usbhaudio.obj: ../usblib/host/usbhaudio.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"/opt/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.6.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me -Ooff --include_path="/opt/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.6.LTS/include" --include_path="/home/andres/workspace_v7/base-practica-TIVA-2018" --include_path="/home/andres/workspace_v7/base-practica-TIVA-2018/FreeRTOS/Source/include" --include_path="/home/andres/workspace_v7/base-practica-TIVA-2018/FreeRTOS/Source/portable/CCS/ARM_CM4F" --define=ccs="ccs" --define=TARGET_IS_BLIZZARD_RB1 --define=UART_BUFFERED --define=WANT_CMDLINE_HISTORY --define=WANT_FREERTOS_SUPPORT --define=PART_TM4C123GH6PM --define=DEBUG -g --c89 --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="usblib/host/usbhaudio.d_raw" --obj_directory="usblib/host" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: "$<"'
	@echo ' '

usblib/host/usbhhid.obj: ../usblib/host/usbhhid.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"/opt/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.6.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me -Ooff --include_path="/opt/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.6.LTS/include" --include_path="/home/andres/workspace_v7/base-practica-TIVA-2018" --include_path="/home/andres/workspace_v7/base-practica-TIVA-2018/FreeRTOS/Source/include" --include_path="/home/andres/workspace_v7/base-practica-TIVA-2018/FreeRTOS/Source/portable/CCS/ARM_CM4F" --define=ccs="ccs" --define=TARGET_IS_BLIZZARD_RB1 --define=UART_BUFFERED --define=WANT_CMDLINE_HISTORY --define=WANT_FREERTOS_SUPPORT --define=PART_TM4C123GH6PM --define=DEBUG -g --c89 --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="usblib/host/usbhhid.d_raw" --obj_directory="usblib/host" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: "$<"'
	@echo ' '

usblib/host/usbhhidkeyboard.obj: ../usblib/host/usbhhidkeyboard.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"/opt/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.6.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me -Ooff --include_path="/opt/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.6.LTS/include" --include_path="/home/andres/workspace_v7/base-practica-TIVA-2018" --include_path="/home/andres/workspace_v7/base-practica-TIVA-2018/FreeRTOS/Source/include" --include_path="/home/andres/workspace_v7/base-practica-TIVA-2018/FreeRTOS/Source/portable/CCS/ARM_CM4F" --define=ccs="ccs" --define=TARGET_IS_BLIZZARD_RB1 --define=UART_BUFFERED --define=WANT_CMDLINE_HISTORY --define=WANT_FREERTOS_SUPPORT --define=PART_TM4C123GH6PM --define=DEBUG -g --c89 --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="usblib/host/usbhhidkeyboard.d_raw" --obj_directory="usblib/host" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: "$<"'
	@echo ' '

usblib/host/usbhhidmouse.obj: ../usblib/host/usbhhidmouse.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"/opt/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.6.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me -Ooff --include_path="/opt/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.6.LTS/include" --include_path="/home/andres/workspace_v7/base-practica-TIVA-2018" --include_path="/home/andres/workspace_v7/base-practica-TIVA-2018/FreeRTOS/Source/include" --include_path="/home/andres/workspace_v7/base-practica-TIVA-2018/FreeRTOS/Source/portable/CCS/ARM_CM4F" --define=ccs="ccs" --define=TARGET_IS_BLIZZARD_RB1 --define=UART_BUFFERED --define=WANT_CMDLINE_HISTORY --define=WANT_FREERTOS_SUPPORT --define=PART_TM4C123GH6PM --define=DEBUG -g --c89 --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="usblib/host/usbhhidmouse.d_raw" --obj_directory="usblib/host" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: "$<"'
	@echo ' '

usblib/host/usbhhub.obj: ../usblib/host/usbhhub.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"/opt/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.6.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me -Ooff --include_path="/opt/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.6.LTS/include" --include_path="/home/andres/workspace_v7/base-practica-TIVA-2018" --include_path="/home/andres/workspace_v7/base-practica-TIVA-2018/FreeRTOS/Source/include" --include_path="/home/andres/workspace_v7/base-practica-TIVA-2018/FreeRTOS/Source/portable/CCS/ARM_CM4F" --define=ccs="ccs" --define=TARGET_IS_BLIZZARD_RB1 --define=UART_BUFFERED --define=WANT_CMDLINE_HISTORY --define=WANT_FREERTOS_SUPPORT --define=PART_TM4C123GH6PM --define=DEBUG -g --c89 --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="usblib/host/usbhhub.d_raw" --obj_directory="usblib/host" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: "$<"'
	@echo ' '

usblib/host/usbhmsc.obj: ../usblib/host/usbhmsc.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"/opt/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.6.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me -Ooff --include_path="/opt/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.6.LTS/include" --include_path="/home/andres/workspace_v7/base-practica-TIVA-2018" --include_path="/home/andres/workspace_v7/base-practica-TIVA-2018/FreeRTOS/Source/include" --include_path="/home/andres/workspace_v7/base-practica-TIVA-2018/FreeRTOS/Source/portable/CCS/ARM_CM4F" --define=ccs="ccs" --define=TARGET_IS_BLIZZARD_RB1 --define=UART_BUFFERED --define=WANT_CMDLINE_HISTORY --define=WANT_FREERTOS_SUPPORT --define=PART_TM4C123GH6PM --define=DEBUG -g --c89 --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="usblib/host/usbhmsc.d_raw" --obj_directory="usblib/host" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: "$<"'
	@echo ' '

usblib/host/usbhostenum.obj: ../usblib/host/usbhostenum.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"/opt/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.6.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me -Ooff --include_path="/opt/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.6.LTS/include" --include_path="/home/andres/workspace_v7/base-practica-TIVA-2018" --include_path="/home/andres/workspace_v7/base-practica-TIVA-2018/FreeRTOS/Source/include" --include_path="/home/andres/workspace_v7/base-practica-TIVA-2018/FreeRTOS/Source/portable/CCS/ARM_CM4F" --define=ccs="ccs" --define=TARGET_IS_BLIZZARD_RB1 --define=UART_BUFFERED --define=WANT_CMDLINE_HISTORY --define=WANT_FREERTOS_SUPPORT --define=PART_TM4C123GH6PM --define=DEBUG -g --c89 --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="usblib/host/usbhostenum.d_raw" --obj_directory="usblib/host" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: "$<"'
	@echo ' '

usblib/host/usbhscsi.obj: ../usblib/host/usbhscsi.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"/opt/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.6.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me -Ooff --include_path="/opt/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.6.LTS/include" --include_path="/home/andres/workspace_v7/base-practica-TIVA-2018" --include_path="/home/andres/workspace_v7/base-practica-TIVA-2018/FreeRTOS/Source/include" --include_path="/home/andres/workspace_v7/base-practica-TIVA-2018/FreeRTOS/Source/portable/CCS/ARM_CM4F" --define=ccs="ccs" --define=TARGET_IS_BLIZZARD_RB1 --define=UART_BUFFERED --define=WANT_CMDLINE_HISTORY --define=WANT_FREERTOS_SUPPORT --define=PART_TM4C123GH6PM --define=DEBUG -g --c89 --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="usblib/host/usbhscsi.d_raw" --obj_directory="usblib/host" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: "$<"'
	@echo ' '


