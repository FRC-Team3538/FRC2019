#pragma once

class Waypoints{
public:
const int kMotionProfileSz =110;		
		
const double kMotionProfile[110][3] = {		
{0,	0	,10},
{0.000227272727272727,	2.727272727	,10},
{0.00102272727272727,	6.818181818	,10},
{0.00261363636363636,	12.27272727	,10},
{0.00522727272727273,	19.09090909	,10},
{0.00909090909090909,	27.27272727	,10},
{0.0144318181818182,	36.81818182	,10},
{0.0214772727272727,	47.72727273	,10},
{0.0304545454545455,	60	,10},
{0.0415909090909091,	73.63636364	,10},
{0.0551136363636364,	88.63636364	,10},
{0.0711363636363636,	103.6363636	,10},
{0.0896590909090909,	118.6363636	,10},
{0.110681818181818,	133.6363636	,10},
{0.134204545454545,	148.6363636	,10},
{0.160227272727273,	163.6363636	,10},
{0.18875,	178.6363636	,10},
{0.219772727272727,	193.6363636	,10},
{0.253295454545455,	208.6363636	,10},
{0.289318181818182,	223.6363636	,10},
{0.327840909090909,	238.6363636	,10},
{0.368863636363636,	253.6363636	,10},
{0.412386363636364,	268.6363636	,10},
{0.458409090909091,	283.6363636	,10},
{0.506931818181818,	298.6363636	,10},
{0.557954545454546,	313.6363636	,10},
{0.611477272727273,	328.6363636	,10},
{0.6675,	343.6363636	,10},
{0.726022727272727,	358.6363636	,10},
{0.787045454545455,	373.6363636	,10},
{0.850568181818182,	388.6363636	,10},
{0.916590909090909,	403.6363636	,10},
{0.985113636363637,	418.6363636	,10},
{1.05613636363636,	433.6363636	,10},
{1.12965909090909,	448.6363636	,10},
{1.20568181818182,	463.6363636	,10},
{1.28420454545455,	478.6363636	,10},
{1.36522727272727,	493.6363636	,10},
{1.44875,	508.6363636	,10},
{1.53477272727273,	523.6363636	,10},
{1.62329545454546,	538.6363636	,10},
{1.71409090909091,	550.9090909	,10},
{1.80681818181818,	561.8181818	,10},
{1.90125,	571.3636364	,10},
{1.99715909090909,	579.5454545	,10},
{2.09431818181818,	586.3636364	,10},
{2.1925,	591.8181818	,10},
{2.29147727272727,	595.9090909	,10},
{2.39102272727273,	598.6363636	,10},
{2.49090909090909,	600	,10},
{2.59090909090909,	600	,10},
{2.69090909090909,	600	,10},
{2.79090909090909,	600	,10},
{2.89090909090909,	600	,10},
{2.99090909090909,	600	,10},
{3.09090909090909,	600	,10},
{3.19090909090909,	600	,10},
{3.29090909090909,	600	,10},
{3.39090909090909,	600	,10},
{3.49090909090909,	600	,10},
{3.59090909090909,	600	,10},
{3.69068181818182,	597.2727273	,10},
{3.78988636363637,	593.1818182	,10},
{3.88829545454546,	587.7272727	,10},
{3.98568181818182,	580.9090909	,10},
{4.08181818181818,	572.7272727	,10},
{4.17647727272728,	563.1818182	,10},
{4.26943181818182,	552.2727273	,10},
{4.36045454545455,	540	,10},
{4.44931818181818,	526.3636364	,10},
{4.53579545454546,	511.3636364	,10},
{4.61977272727273,	496.3636364	,10},
{4.70125,	481.3636364	,10},
{4.78022727272727,	466.3636364	,10},
{4.85670454545455,	451.3636364	,10},
{4.93068181818182,	436.3636364	,10},
{5.00215909090909,	421.3636364	,10},
{5.07113636363637,	406.3636364	,10},
{5.13761363636364,	391.3636364	,10},
{5.20159090909091,	376.3636364	,10},
{5.26306818181818,	361.3636364	,10},
{5.32204545454546,	346.3636364	,10},
{5.37852272727273,	331.3636364	,10},
{5.4325,	316.3636364	,10},
{5.48397727272727,	301.3636364	,10},
{5.53295454545455,	286.3636364	,10},
{5.57943181818182,	271.3636364	,10},
{5.62340909090909,	256.3636364	,10},
{5.66488636363637,	241.3636364	,10},
{5.70386363636364,	226.3636364	,10},
{5.74034090909091,	211.3636364	,10},
{5.77431818181818,	196.3636364	,10},
{5.80579545454546,	181.3636364	,10},
{5.83477272727273,	166.3636364	,10},
{5.86125,	151.3636364	,10},
{5.88522727272727,	136.3636364	,10},
{5.90670454545455,	121.3636364	,10},
{5.92568181818182,	106.3636364	,10},
{5.94215909090909,	91.36363636	,10},
{5.95613636363636,	76.36363636	,10},
{5.96761363636364,	61.36363636	,10},
{5.97681818181818,	49.09090909	,10},
{5.98409090909091,	38.18181818	,10},
{5.98965909090909,	28.63636364	,10},
{5.99375,	20.45454545	,10},
{5.99659090909091,	13.63636364	,10},
{5.99840909090909,	8.181818182	,10},
{5.99943181818182,	4.090909091	,10},
{5.99988636363636,	1.363636364	,10},
{6,	0	,10}};
};