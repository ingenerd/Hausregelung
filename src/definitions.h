#ifndef DEFINITIONS_H_
#define DEFINITIONS_H_

const int BREITE       = 800;
const int HOEHE        = 480;
const int RAND         =  10;
const int TOGGLEBREITE =  50; //Breite der Togglebuttons (sofern diese nicht anderweitig größer angelegt werden...)
const int SPACER       =   5; //Abstand zwischen Togglebuttons und Mitte

//Temperatur-Namen, die so leserlicher Funktionen übergeben werden können
enum class ZimmerTemp {
  Elt_IST, Elt_SOLL, 
  Bad_IST, Bad_SOLL, 
  KiVo_IST, KiVo_SOLL, 
  KiHi_IST, KiHi_SOLL
};

//Rolladen-Namen, die so leserlicher Funktionen übergeben werden können
enum class ZimmerRolladen {
  Elt_Roll,
  Bad_Roll,
  KiVo1_Roll,
  KiVo2_Roll,
  KiHi1_Roll,
  KiHi2_Roll,
};

//Arten, die in der Anzeige gezeigt und durchgetoggelt werden können
enum class Visualisierung {
  Grundriss, Schema, Wetter
};

//Farben
#define bjsYellowLight   0.949019607843137 , 0.874509803921569, 0.270588235294118
#define bjsYellowRegular 0.890196078431372 , 0.792156862745098, 0
#define bjsYellowDark    0.729411764705882 , 0.588235294117647, 0
#define bjsOrangeLight   0.949019607843137 , 0.647058823529412, 0.203921568627451
#define bjsOrangeRegular 0.92156862745098  , 0.435294117647059, 0
#define bjsOrangeDark    0.768627450980392 , 0.32156862745098 , 0
#define bjsBrownLight    0.717647058823529 , 0.529411764705882, 0.235294117647059
#define bjsBrownRegular  0.56078431372549  , 0.294117647058823, 0.0666666666666667
#define bjsBrownDark     0.364705882352941 , 0.152941176470588, 0.00784313725490196
#define bjsRedLight      0.898039215686275 , 0.12156862745098 , 0.12156862745098
#define bjsRedRegular    0.76078431372549  , 0                , 0
#define bjsRedDark       0.603921568627451 , 0                , 0
#define bjsGreenLight    0.345098039215686 , 0.690196078431373, 0.00784313725490196
#define bjsGreenRegular  0.254901960784314 , 0.627450980392157, 0.0862745098039216
#define bjsGreenDark     0.109803921568627 , 0.407843137254902, 0.0235294117647059
#define bjsBlueLight     0.349019607843137 , 0.525490196078431, 0.713725490196078
#define bjsBlueRegular   0.105882352941176 , 0.298039215686274, 0.545098039215686
#define bjsBlueDark      0.0274509803921569, 0.192156862745098, 0.431372549019608
#define bjsVioletLight   0.580392156862745 , 0.4              , 0.56078431372549
#define bjsVioletRegular 0.36078431372549  , 0.215686274509804, 0.384313725490196
#define bjsVioletDark    0.262745098039216 , 0.109803921568627, 0.301960784313725
#define bjsGreyLight     0.827450980392157 , 0.843137254901961, 0.811764705882353
#define bjsGreyRegular   0.533333333333333 , 0.541176470588235, 0.52156862745098
#define bjsGreyDark      0.180392156862745 , 0.203921568627451, 0.211764705882353

#endif /* DEFINITIONS_H_ */