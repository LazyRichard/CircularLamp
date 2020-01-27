EESchema Schematic File Version 4
LIBS:switch-cache
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
L Device:Rotary_Encoder_Switch SW1
U 1 1 5C766288
P 5350 4200
F 0 "SW1" H 5350 4567 50  0000 C CNN
F 1 "Rotary_Encoder_Switch" H 5350 4476 50  0000 C CNN
F 2 "User:EC12B24S2033ZZZ" H 5200 4360 50  0001 C CNN
F 3 "~" H 5350 4460 50  0001 C CNN
	1    5350 4200
	1    0    0    -1  
$EndComp
Text Label 4850 4200 0    50   ~ 0
GND
Wire Wire Line
	4850 4200 5050 4200
Text Label 5750 4300 0    50   ~ 0
GND
Wire Wire Line
	5650 4300 5750 4300
Text Label 4850 4100 0    50   ~ 0
A
Text Label 4850 4300 0    50   ~ 0
B
Wire Wire Line
	4850 4300 5050 4300
Wire Wire Line
	4850 4100 5050 4100
Text Label 5750 4100 0    50   ~ 0
SW
Wire Wire Line
	5750 4100 5650 4100
$Comp
L Connector:Conn_01x04_Male J1
U 1 1 5C76A352
P 6500 4200
F 0 "J1" H 6473 4080 50  0000 R CNN
F 1 "Conn_01x04_Male" H 6473 4171 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x04_P2.54mm_Vertical" H 6500 4200 50  0001 C CNN
F 3 "~" H 6500 4200 50  0001 C CNN
	1    6500 4200
	-1   0    0    1   
$EndComp
Text Label 6100 4300 0    50   ~ 0
A
Text Label 6100 4200 0    50   ~ 0
B
Text Label 6100 4100 0    50   ~ 0
SW
Text Label 6100 4000 0    50   ~ 0
GND
Wire Wire Line
	6100 4000 6300 4000
Wire Wire Line
	6100 4100 6300 4100
Wire Wire Line
	6100 4200 6300 4200
Wire Wire Line
	6100 4300 6300 4300
$Comp
L Mechanical:MountingHole H1
U 1 1 5C76A78E
P 7500 4000
F 0 "H1" H 7600 4046 50  0000 L CNN
F 1 "MountingHole" H 7600 3955 50  0000 L CNN
F 2 "MountingHole:MountingHole_2.2mm_M2" H 7500 4000 50  0001 C CNN
F 3 "~" H 7500 4000 50  0001 C CNN
	1    7500 4000
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole H2
U 1 1 5C76A7FA
P 7500 4200
F 0 "H2" H 7600 4246 50  0000 L CNN
F 1 "MountingHole" H 7600 4155 50  0000 L CNN
F 2 "MountingHole:MountingHole_2.2mm_M2" H 7500 4200 50  0001 C CNN
F 3 "~" H 7500 4200 50  0001 C CNN
	1    7500 4200
	1    0    0    -1  
$EndComp
$EndSCHEMATC
