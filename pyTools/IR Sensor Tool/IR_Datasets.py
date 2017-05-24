"""
Created on 03/25/2017
Python 3.6.1

@author: Javier



This script contains data taken from testing different IR Sensor configurations.

Each dataset is stored in a specific dictionary named after the date it was
taken at in the format of:
    dataset_date = {
    'distance1':readingValue1
    'distance2':readingValue2
    ...
    'distanceN':readingValueN
    }
"""



MFv20_1 = {
'2.0' :0.936996,
'3.0' :0.911416,
'4.0' :0.876313,
'5.0' :0.845360,
'7.5' :0.662943,
'10.0':0.432906,
'12.5':0.306105,
'15.0':0.234737,
'17.5':0.189805,
'20.0':0.160562,
'22.5':0.140476,
'25.0':0.126252,
'27.5':0.115140,
'30.0':0.107387,
'32.5':0.101770,
'35.0':0.097070,
'37.5':0.093529,

#'40.0':0.090476,
#'45.0':0.086386,
#'50.0':0.083700,
#'55.0':0.081868,
#'60.0':0.080586,

'noWall':0.075824,  # Turn on Emitter without a wall to bounce back light
'ambLight':0.000611, # Read from Receiver without turning on Emitter

# General Info
'date': '2016_04_25',
'Distance Metric': 'cm',
'Reading Metric': 'ADC Value',

'Emitter': 'SFH4545',
'Emitter Voltage':  '5V',
'Emitter Resistor': '20 ohms',
'Emitter Capacitor':'4.7 uF',

'Receiver':'TEFT4300',
'Receiver Voltage': '3.3V',
'Receiver Resistor':'1240 ohms'
}


MFv21_18ohm_2_2uF = {
'2.0': 0.8812,
'3.0': 0.8144,
'4.0': 0.6602,
'5.0': 0.4435,
'6.0': 0.2973,
'7.0': 0.2492,
'8.0': 0.1757,
'9.0': 0.1388,
'10.0': 0.1176,
'11.0': 0.0843,
'12.0': 0.0796,
'13.0': 0.0615,
'14.0': 0.0590,

'15.0': 0.0473,
'18.0': 0.0331,
'21.0': 0.0248,
'24.0': 0.0199,
'27.0': 0.0152,
'30.0': 0.0135,
'33.0': 0.0110,

# General Info
'Emitter': 'SFH4545',
'Emitter Voltage':  '3.3V',
'Emitter Resistor': '18 ohms',
'Emitter Capacitor':'2.2 uF',

'Receiver':'TEFT4300',
'Receiver Voltage': '3.3V',
'Receiver Resistor':'1240 ohms'
}



# Choose which dataset to be used
DATASET_CHOICE = MFv21_18ohm_2_2uF


# Function that returns choosen dataset
def get_dataset():
    return DATASET_CHOICE