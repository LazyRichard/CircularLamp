EESchema Schematic File Version 4
LIBS:controller-cache
EELAYER 26 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L ESP8266:NodeMCU_1.0_(ESP-12E) U2
U 1 1 5C6FE9F1
P 5950 3650
F 0 "U2" H 5950 4843 60  0000 C CNN
F 1 "NodeMCU_1.0_(ESP-12E)" H 5950 4737 60  0000 C CNN
F 2 "ESP8266:NodeMCU-LoLinV3" H 5950 4631 60  0000 C CNN
F 3 "" H 5350 2800 60  0000 C CNN
	1    5950 3650
	1    0    0    -1  
$EndComp
$Comp
L Connector:Jack-DC J1
U 1 1 5C6FEAED
P 2400 1450
F 0 "J1" H 2455 1775 50  0000 C CNN
F 1 "Jack-DC" H 2455 1684 50  0000 C CNN
F 2 "Connector_BarrelJack:BarrelJack_Horizontal" H 2450 1410 50  0001 C CNN
F 3 "~" H 2450 1410 50  0001 C CNN
	1    2400 1450
	1    0    0    -1  
$EndComp
Wire Wire Line
	2700 1350 2850 1350
Wire Wire Line
	2700 1550 2850 1550
$Comp
L Connector:Conn_01x02_Female J3
U 1 1 5C6FF4D7
P 7300 3250
F 0 "J3" H 7327 3226 50  0000 L CNN
F 1 "SERIAL_OUT" H 7327 3135 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 7300 3250 50  0001 C CNN
F 3 "~" H 7300 3250 50  0001 C CNN
	1    7300 3250
	1    0    0    -1  
$EndComp
Text Label 7050 3250 0    50   ~ 0
BI
Text Label 7050 3350 0    50   ~ 0
DI
$Comp
L pspice:CAP C1
U 1 1 5C6FFEB8
P 1500 3750
F 0 "C1" H 1678 3796 50  0000 L CNN
F 1 "100uF" H 1678 3705 50  0000 L CNN
F 2 "Capacitor_THT:CP_Radial_D8.0mm_P3.50mm" H 1500 3750 50  0001 C CNN
F 3 "~" H 1500 3750 50  0001 C CNN
	1    1500 3750
	1    0    0    -1  
$EndComp
Wire Wire Line
	1500 3500 1500 3400
Wire Wire Line
	1500 3400 2000 3400
Wire Wire Line
	2000 3600 1950 3600
Wire Wire Line
	1500 4250 1950 4250
Connection ~ 1950 4250
Wire Wire Line
	1950 4250 2500 4250
Connection ~ 2500 4250
Wire Wire Line
	3000 3600 3100 3600
Wire Wire Line
	3100 3600 3100 3700
$Comp
L pspice:INDUCTOR L1
U 1 1 5C701FB7
P 3450 3600
F 0 "L1" H 3450 3815 50  0000 C CNN
F 1 "330uH" H 3450 3724 50  0000 C CNN
F 2 "Inductor_SMD:L_Taiyo-Yuden_NR-50xx_HandSoldering" H 3450 3600 50  0001 C CNN
F 3 "~" H 3450 3600 50  0001 C CNN
	1    3450 3600
	1    0    0    -1  
$EndComp
Wire Wire Line
	3000 3400 3800 3400
Wire Wire Line
	3800 3400 3800 3600
Wire Wire Line
	3800 3600 3700 3600
Wire Wire Line
	3200 3600 3100 3600
Connection ~ 3100 3600
Wire Wire Line
	3800 3600 3950 3600
Connection ~ 3800 3600
$Comp
L pspice:CAP C2
U 1 1 5C702BD9
P 3800 3950
F 0 "C2" H 3978 3996 50  0000 L CNN
F 1 "330uF" H 3978 3905 50  0000 L CNN
F 2 "Capacitor_THT:CP_Radial_D8.0mm_P3.50mm" H 3800 3950 50  0001 C CNN
F 3 "~" H 3800 3950 50  0001 C CNN
	1    3800 3950
	1    0    0    -1  
$EndComp
Wire Wire Line
	3800 3600 3800 3700
Wire Wire Line
	3800 4200 3800 4250
Wire Wire Line
	1500 4000 1500 4250
Wire Wire Line
	1950 3600 1950 4250
Wire Wire Line
	2500 3800 2500 4250
Wire Wire Line
	3950 4250 3800 4250
Connection ~ 3800 4250
$Comp
L Device:D_Schottky D1
U 1 1 5C708737
P 3100 3850
F 0 "D1" H 3100 4066 50  0000 C CNN
F 1 "SS14" H 3100 3975 50  0000 C CNN
F 2 "Diode_SMD:D_SMA_Handsoldering" H 3100 3850 50  0001 C CNN
F 3 "~" H 3100 3850 50  0001 C CNN
	1    3100 3850
	0    1    1    0   
$EndComp
Wire Wire Line
	2500 4250 3100 4250
Wire Wire Line
	3100 4000 3100 4250
Connection ~ 3100 4250
Wire Wire Line
	3100 4250 3800 4250
$Comp
L Connector:Micro_SD_Card J4
U 1 1 5C712DBD
P 9400 3750
F 0 "J4" H 9350 4467 50  0000 C CNN
F 1 "Micro_SD_Card" H 9350 4376 50  0000 C CNN
F 2 "User:MSDC-M61408" H 10550 4050 50  0001 C CNN
F 3 "http://katalog.we-online.de/em/datasheet/693072010801.pdf" H 9400 3750 50  0001 C CNN
	1    9400 3750
	1    0    0    -1  
$EndComp
$Comp
L Regulator_Switching:LM2575-3.3BU U1
U 1 1 5C7130CF
P 2500 3500
F 0 "U1" H 2500 3867 50  0000 C CNN
F 1 "LM2575-3.3BU" H 2500 3776 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:TO-263-5_TabPin3" H 2500 3250 50  0001 L CIN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/lm2575.pdf" H 2500 3500 50  0001 C CNN
	1    2500 3500
	1    0    0    -1  
$EndComp
Wire Wire Line
	6750 3250 7100 3250
Wire Wire Line
	6750 3350 7100 3350
Text Label 7000 4250 0    50   ~ 0
GND
Text Label 4850 3850 0    50   ~ 0
GND
Text Label 4850 3950 0    50   ~ 0
VOUT
Text Label 4850 4250 0    50   ~ 0
GND
Wire Wire Line
	4850 4250 5150 4250
Wire Wire Line
	4850 3950 5150 3950
Wire Wire Line
	4850 3850 5150 3850
Text Label 7000 4350 0    50   ~ 0
VOUT
Wire Wire Line
	6750 4250 7000 4250
Wire Wire Line
	6750 4350 7000 4350
Text Label 3950 4250 0    50   ~ 0
GND
Text Label 3950 3600 0    50   ~ 0
VOUT
Text Label 2850 1350 0    50   ~ 0
VSW
Text Label 2850 1550 0    50   ~ 0
GND
Wire Wire Line
	1500 3400 1300 3400
Connection ~ 1500 3400
Text Label 1300 3400 0    50   ~ 0
VIN
Text Label 8200 3750 0    50   ~ 0
VOUT
Text Label 8200 3950 0    50   ~ 0
GND
Text Label 10300 4350 0    50   ~ 0
GND
Wire Wire Line
	10200 4350 10300 4350
Wire Wire Line
	8200 3950 8500 3950
Wire Wire Line
	8200 3750 8500 3750
$Comp
L Connector:Screw_Terminal_01x02 J2
U 1 1 5C721C7E
P 2000 2200
F 0 "J2" H 1920 1875 50  0000 C CNN
F 1 "Screw_Terminal_01x02" H 1920 1966 50  0000 C CNN
F 2 "ctl:PAD-2" H 2000 2200 50  0001 C CNN
F 3 "~" H 2000 2200 50  0001 C CNN
	1    2000 2200
	-1   0    0    1   
$EndComp
Wire Wire Line
	2200 2100 2350 2100
Wire Wire Line
	2200 2200 2350 2200
Text Label 2350 2100 0    50   ~ 0
VIN
Text Label 2350 2200 0    50   ~ 0
GND
$Comp
L Connector:Screw_Terminal_01x02 J6
U 1 1 5C742A4D
P 2900 2200
F 0 "J6" H 2820 1875 50  0000 C CNN
F 1 "Screw_Terminal_01x02" H 2820 1966 50  0000 C CNN
F 2 "ctl:PAD-2" H 2900 2200 50  0001 C CNN
F 3 "~" H 2900 2200 50  0001 C CNN
	1    2900 2200
	-1   0    0    1   
$EndComp
Wire Wire Line
	3100 2100 3250 2100
Wire Wire Line
	3100 2200 3250 2200
Text Label 3250 2100 0    50   ~ 0
VIN
Text Label 3250 2200 0    50   ~ 0
GND
$Comp
L Connector:Screw_Terminal_01x02 J5
U 1 1 5C74315D
P 2000 2700
F 0 "J5" H 1920 2375 50  0000 C CNN
F 1 "Screw_Terminal_01x02" H 1920 2466 50  0000 C CNN
F 2 "ctl:PAD-2" H 2000 2700 50  0001 C CNN
F 3 "~" H 2000 2700 50  0001 C CNN
	1    2000 2700
	-1   0    0    1   
$EndComp
Wire Wire Line
	2200 2600 2350 2600
Wire Wire Line
	2200 2700 2350 2700
Text Label 2350 2600 0    50   ~ 0
VIN
Text Label 2350 2700 0    50   ~ 0
GND
$Comp
L Connector:Screw_Terminal_01x02 J7
U 1 1 5C743922
P 2950 2700
F 0 "J7" H 2870 2375 50  0000 C CNN
F 1 "Screw_Terminal_01x02" H 2870 2466 50  0000 C CNN
F 2 "ctl:PAD-2" H 2950 2700 50  0001 C CNN
F 3 "~" H 2950 2700 50  0001 C CNN
	1    2950 2700
	-1   0    0    1   
$EndComp
Wire Wire Line
	3150 2600 3300 2600
Wire Wire Line
	3150 2700 3300 2700
Text Label 3300 2600 0    50   ~ 0
VIN
Text Label 3300 2700 0    50   ~ 0
GND
Text Label 7000 3450 0    50   ~ 0
VOUT
Wire Wire Line
	6750 3450 7000 3450
Wire Wire Line
	6750 3650 7000 3650
Wire Wire Line
	6750 3750 7000 3750
Wire Wire Line
	6750 3850 7000 3850
Wire Wire Line
	6750 3950 7000 3950
Wire Wire Line
	8500 3650 8200 3650
Wire Wire Line
	8500 3850 8200 3850
Wire Wire Line
	8500 4050 8200 4050
Wire Wire Line
	8500 3550 8200 3550
Text Label 8200 3850 0    50   ~ 0
CLK
Text Label 7000 3650 0    50   ~ 0
CLK
Text Label 7000 3750 0    50   ~ 0
DAT0
Text Label 8200 4050 0    50   ~ 0
DAT0
Text Label 8200 3650 0    50   ~ 0
CMD
Text Label 7000 3850 0    50   ~ 0
CMD
Text Label 7000 3950 0    50   ~ 0
DAT3
Text Label 8200 3550 0    50   ~ 0
DAT3
NoConn ~ 8500 3450
NoConn ~ 8500 4150
Text Label 7000 3550 0    50   ~ 0
GND
Wire Wire Line
	6750 3550 7000 3550
Text Label 7000 2950 0    50   ~ 0
D0
Text Label 7000 3050 0    50   ~ 0
D1
Text Label 7000 3150 0    50   ~ 0
D2
Text Label 7000 4050 0    50   ~ 0
RX
Text Label 7000 4150 0    50   ~ 0
TX
Text Label 4900 2950 0    50   ~ 0
A0
Wire Wire Line
	4900 2950 5150 2950
Wire Wire Line
	6750 4050 7000 4050
Wire Wire Line
	6750 4150 7000 4150
Wire Wire Line
	6750 2950 7000 2950
Wire Wire Line
	6750 3050 7000 3050
Wire Wire Line
	6750 3150 7000 3150
Text Label 7100 2300 0    50   ~ 0
VOUT
Text Label 7100 1600 0    50   ~ 0
GND
Text Label 7100 2100 0    50   ~ 0
D0
Text Label 7100 2000 0    50   ~ 0
D1
Text Label 7100 1900 0    50   ~ 0
D2
Text Label 7100 2200 0    50   ~ 0
A0
Wire Wire Line
	7100 2300 7450 2300
Wire Wire Line
	7100 1600 7450 1600
Wire Wire Line
	7100 2100 7450 2100
Wire Wire Line
	7100 2000 7450 2000
Wire Wire Line
	7100 1900 7450 1900
Wire Wire Line
	7100 2200 7450 2200
$Comp
L Connector:Conn_01x08_Male J8
U 1 1 5C796005
P 7650 2000
F 0 "J8" H 7623 1880 50  0000 R CNN
F 1 "Conn_01x08_Male" H 7623 1971 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x08_P2.54mm_Vertical" H 7650 2000 50  0001 C CNN
F 3 "~" H 7650 2000 50  0001 C CNN
	1    7650 2000
	-1   0    0    1   
$EndComp
Text Label 7100 1700 0    50   ~ 0
VOUT
Wire Wire Line
	7100 1700 7450 1700
$Comp
L Connector:Screw_Terminal_01x02 J9
U 1 1 5C7A1D68
P 3850 2700
F 0 "J9" H 3770 2375 50  0000 C CNN
F 1 "Screw_Terminal_01x02" H 3770 2466 50  0000 C CNN
F 2 "ctl:PAD-2" H 3850 2700 50  0001 C CNN
F 3 "~" H 3850 2700 50  0001 C CNN
	1    3850 2700
	-1   0    0    1   
$EndComp
Wire Wire Line
	4050 2600 4200 2600
Wire Wire Line
	4050 2700 4200 2700
Text Label 4200 2600 0    50   ~ 0
VIN
Text Label 4200 2700 0    50   ~ 0
VSW
$EndSCHEMATC
