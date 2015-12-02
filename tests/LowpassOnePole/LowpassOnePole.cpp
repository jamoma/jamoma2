/** @file
	@ingroup 	jamoma2
 
	@brief 		Unit test for the Dcblocker class
 
	@author		Timothy Place, Nathan Wolek
	@copyright	Copyright (c) 2005-2015 The Jamoma Group, http://jamoma.org.
	@license	This project is released under the terms of the MIT License.

 */

#include "Jamoma.h"


class LowpassOnePoleTest {
	
	Jamoma::UnitTest<LowpassOnePoleTest>*	mTest;
	
public:
	LowpassOnePoleTest(Jamoma::UnitTest<LowpassOnePoleTest>* test)
	: mTest(test)
	{
		testImpulseResponse();
	}

	
	void testImpulseResponse()
	{
		Jamoma::LowpassOnePole my_lowpass;
		
		my_lowpass.coefficient = 0.5;
		
		Jamoma::UnitImpulse impulse;
		
		impulse.channelCount = 1;
		impulse.frameCount = 64;
		
		auto out_samples = my_lowpass( impulse() );
		
		// The following impulse was based on the code from jamoma
		// implemented in Processing by NW
		Jamoma::SampleVector expectedIR = {
			0.5,
			0.25,
			0.125,
			0.0625,
			0.03125,
			0.015625,
			0.0078125,
			0.00390625,
			0.001953125,
			9.765625E-4,
			4.8828125E-4,
			2.44140625E-4,
			1.220703125E-4,
			6.103515625E-5,
			3.0517578125E-5,
			1.52587890625E-5,
			7.62939453125E-6,
			3.814697265625E-6,
			1.9073486328125E-6,
			9.5367431640625E-7,
			4.76837158203125E-7,
			2.384185791015625E-7,
			1.1920928955078125E-7,
			5.9604644775390625E-8,
			2.9802322387695312E-8,
			1.4901161193847656E-8,
			7.450580596923828E-9,
			3.725290298461914E-9,
			1.862645149230957E-9,
			9.313225746154785E-10,
			4.6566128730773926E-10,
			2.3283064365386963E-10,
			1.1641532182693481E-10,
			5.820766091346741E-11,
			2.9103830456733704E-11,
			1.4551915228366852E-11,
			7.275957614183426E-12,
			3.637978807091713E-12,
			1.8189894035458565E-12,
			9.094947017729282E-13,
			4.547473508864641E-13,
			2.2737367544323206E-13,
			1.1368683772161603E-13,
			5.6843418860808015E-14,
			2.8421709430404007E-14,
			1.4210854715202004E-14,
			7.105427357601002E-15,
			3.552713678800501E-15,
			1.7763568394002505E-15,
			8.881784197001252E-16,
			4.440892098500626E-16,
			2.220446049250313E-16,
			1.1102230246251565E-16,
			5.551115123125783E-17,
			2.7755575615628914E-17,
			1.3877787807814457E-17,
			6.938893903907228E-18,
			3.469446951953614E-18,
			1.734723475976807E-18,
			8.673617379884035E-19,
			4.3368086899420177E-19,
			2.1684043449710089E-19,
			1.0842021724855044E-19,
			5.421010862427522E-20
		};
		
		int badSampleCount = 0;
		Jamoma::Sample temp = 0.0;
		Jamoma::Sample tempExpected = 0.0;
		
		for (int i = 0; i < expectedIR.size(); i++)
		{
			temp = out_samples[0][0][i];
			tempExpected = expectedIR[i];
			if (! mTest->compare(temp, tempExpected) ) {
				badSampleCount++;
				std::cout << "sample " << i << " had a difference of " << std::fabs(temp - tempExpected) << std::endl;
			}
		}
		
		std::cout << "the impulse response of my_lowpass (1 pole) has " << badSampleCount << " bad samples" << std::endl;
		mTest->TEST_ASSERT("Bad Sample Count", badSampleCount == 0);
		
		// testing range limitations
		my_lowpass.coefficient = 0.7;
		mTest->TEST_ASSERT("coefficient setting", my_lowpass.coefficient == 0.7);
		
		my_lowpass.coefficient = -1.0;
		mTest->TEST_ASSERT("low coefficient limiting", my_lowpass.coefficient == 0.0);
		
		my_lowpass.coefficient = 1.2;
		mTest->TEST_ASSERT("high coefficient limiting", my_lowpass.coefficient == 1.0);
		
		
		// Testing coefficient setting via frequency
		// The following Max 7 patcher can be convenient as an interactive reference for the
		// relationship between frequency response and coefficient
		/*
		 
		 <pre><code>
		 ----------begin_max5_patcher----------
		 2115.3oc6asrjiZCEcc2eEJplEcRY6fdAlYURVjJUMS9BRkpKYiraxfAG.mz
		 8L0ju8nm.1FroaaHdQVLF8BoiNb0U2G87k6uCtH6YQAD7dvuAt6tub+c2oaR
		 0vc152A2vedYBuPOL3FQQAes.NwzWo34Rc6XOOWawQ5VxV7GSCpZrn7kDgtc
		 WKY6JSDkkurUXVeHD761tR2sINU1odIw1F2xKW9Tb55GyEKKMuBwmMyaB.6o
		 9kfzkIy7plms4hBQZIuLNKcuWiV+ZteZt3FnoWcjpwud+8pelzSNJU72xM+Q
		 Tj34s4.zLvTfrzCSwx076.jYHJhIK7tUHv2CnTjm2rusEpze9kSkntoRJSSD
		 gdFR7Xt7xokSH5H2ysskoCpziOogzCcdekd7I9CpzypjL4jzFcPdMzwD.bAO
		 c8aVR.gYlGdGQLqxx2v0i1uZZx4aDkh7GEo7EFr4cZZjxLLNB0CdDeEE2Prt
		 D2PCp3FK3MItwlqE2PgCj3VmzTmmJGVc5Lq.2qkln3A8T41jrx+oE1fE5Zju
		 KJNak5bPQ7m06ejGlNwMW4qiSs2zp2TyqgKqITuBTH0vcgZ4MeGSx1mO1lEm
		 ZlIFxMW4REFhD9BQhd+8q70owk6hDfGh9op6jhx1vkvnZT+bt3O2IRW9B3ge
		 4yUi5.Fuw5JIx81.E6VT0lxJjpO.x9Vlkjka5vaFch6m.l7.Q81QI19T7xOk
		 JLerTZTbcn2lOVKollk5j0k8lDmJZzopJOutaIbWH0o00auJNQpxS2AuLKZQ
		 cOFNR9h7b82DuFHx1mHUKDgwdrV5sAlxVez7Jkl9jH2xXtY.XtGUqqvUXtqP
		 fqfuq.yUf5JPbEvtBHWA2L6lX275lV2r5lT2b5lRbCj4.lCWNX4PkCTNL4fj
		 CQN.YwiENVzXAiEKVnXQhEHVbXggEEVPXwfEBVDz3ZP45aW9ZiklaWayR6NO
		 OwdJjzPaF5P8R0eQ0GmbeP0CSZVDrBuFyqqnQH9CvFeuk89AXi4TeLtV3aJh
		 faHgY50J94cTGceZvz+dxd5keJRq5cJVaU8Ti4QSMptmZXjoAlgL2LjPyPPd
		 ysuucdT37n8QSpwrcUTgcQgxmvp0FJeBqf.T9DVgDn7IrBPP80XNbAkOgUvC
		 JeBqPIT9DVCVnp.rFzJ.XvCwAHBt4Gir7Xol+Ge9P1119K11MMatOpSMfAJo
		 G7b0ujv+WEXkX3oOO8exIiSJF+1EO.+9UzDOZGV3wHCpEdzflV30au1olypi
		 tgv3tXI7vxR3SyRCnilLuwzQSlwLU1E5l4k6v3xrMajxcGI.rpx.23TvSetE
		 BidhXyzW1v52igMr1ffQc9A26JJgKWKTa6J+AU.2YJmwsXBsu5ABI5wyFY0.
		 dyBaiiXCJGgoM4Hb3LV+3H7bbMoNpjDqMRZXiiGx3n6qmjPFIO+QmjZ8z1vd
		 oqyqlNIoAKr2emzLq1t+j9ZtkQdWk5pfW84Gjc6Z7EiL.2h10sFRyjAayRDf
		 jr+dqbv.qoxGSDjvK+1CpKv8l8q01g46caZZYUfolOyavuUAAdWax4jfgUio
		 8PsQbmv56sJAFqKwCV.D6hldGBzVlyHCrNyfyPSCn4kD7nXdoSR.2HlL2l1W
		 JDQK3K+DXYlX0p3kwxAAdXwin1RCHw6xUVfCZxLsYqYWGRrWhPl2iCIdWuqP
		 9lofVuBAGNdWg32URlGtqPVykNbrmPA+Qu1DJPjqfPgMRkcKTb4ed6Tkv3nQ
		 vY7yMiFgtRpDoxyqqediNA+DtWhivAmKwQTT64MhuYahNuQckxnB0HDEmNWQ
		 CQdgXcFTzkw4KS5Nrnlvw8VBK59cz+nhROcHQOHBjsEUTZi61sGtajAZiZMS
		 JIX8JuDl3cCTlqXeOHxjUh57UXVGn5VJ65Ck14ehHv5MC2U7WIrKK0Dx2W8q
		 Nl45hX0OHcQjd+xrWhM0Tdpt8olwnP1IChqF5.ndbP2KqphTUsYpvTT0QU6X
		 cEroBQWg.fibHg6RyCE+ehlGeS3+5slmNSY81m3EBvC47nXdZQm4rNUonOQ5
		 MTDnJ5d2RZiFnTz7V0EgtTUQVSEQUmBIUrj9Ln+DW1szI25nbacFsQUGpf1o
		 UVlBsSrrrOzN0xxpj2gLuK5jIMcnxLjKcoFUnSsoI0jyTSdTOVabmYBUq4wl
		 3QiZHaJLo5J1LX5qqXye4b.rZ0UYyDre1TGcUQcXyuQrMRTxiSZyhwpvHnBr
		 QpzHMcW+XdLO4UZL4Q+6sZXIkpeD1VpLZD7ERGAew+5QdQwKKmsU4SYwxmDa
		 3uG3nyh30o.45Jx4kY4uGDIRyjaRSkenT9ccsTREf.31Hc+qBoqPmzwRd9Kc
		 P0jyS017hgCeabcS2zzuo9j6A+kPqWdU66+AnHaW9R2dw8mlKnF.RRtTwnxs
		 XyAQ1aPOEGIo9ltSDEWn7vHpamq5KdB75AdXdiFdX8AOGPhCId7o2V7yAhFs
		 iG73AGzMF8biINqt5473Ib7NdguwNtStsvC0+l53kJkw2RvgdaAmaKcgz9n6
		 gLd3AG1C7PGuyVj9nKTY1H.ON3g1W7fFG7zGcyGPhCp7SefC8lBN3w6lTbut
		 oHXbszfdtOW9mAOahipibl5uoHlJ7Kz.cjBBo5+TPz0pWnq6N.cN8U3W2N.E
		 FpBVDMP67muD5LasytCL95w2t8ujd4ZQgF7R2p+CSP7BlnqFmZppc6GlK9qX
		 230nBxyktlVJ8KcWtwc2ms+2UDtIKRjmtK15moj1t25V7A9WV4.cIeqwYYIA
		 shuKobeVsoy1RJ6iRm0AeLd8SprYZ1aSreTxERR5.GvgajSXriHzAo4q2+u.
		 80vVA
		 -----------end_max5_patcher-----------
		 </code></pre>
		 
		 */
		
		my_lowpass.sampleRate = 96000;
		
		my_lowpass.frequency = 1000.0; // hz
		mTest->TEST_ASSERT("coefficient for 1K cutoff @ 96K fs", mTest->compare((double)my_lowpass.coefficient, 0.06335217076965427));
		
		my_lowpass.frequency = 4000.0; // hz
		mTest->TEST_ASSERT("coefficient for 1K cutoff @ 96K fs", mTest->compare((double)my_lowpass.coefficient, 0.23032864479520065));

		my_lowpass.sampleRate = 44100;
		
		my_lowpass.frequency = 1000.0; // hz
		mTest->TEST_ASSERT("coefficient for 1K cutoff @ 44.1K fs", mTest->compare((double)my_lowpass.coefficient, 0.132787865213287));
		
		my_lowpass.frequency = 4000.0; // hz
		mTest->TEST_ASSERT("coefficient for 1K cutoff @ 44.1K fs", mTest->compare((double)my_lowpass.coefficient, 0.43441043913502342));
		
	}

};


int main(int argc, const char * argv[])
{
	Jamoma::UnitTest<LowpassOnePoleTest>	aUnitTestInstance;
	return aUnitTestInstance.failureCount();
}
