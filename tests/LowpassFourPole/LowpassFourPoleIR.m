% @file
% @ingroup 	jamoma2
% 
% @brief 		Generates the ExpectedIR for LowpassFourpoleTest using Octave
%
% @author		Nathan Wolek
% @copyright	Copyright (c) 2005-2015 The Jamoma Group, http://jamoma.org.
% @license		This project is released under the terms of the MIT License.

clear

kPi  = 3.141592653589793238462643383279502884197169399375105820974944592307816406286208998628034825342117068;
kTwoPi  = kPi * 2.0;

in1 = 0.0;
in2 = 0.0;
in3 = 0.0;
in4 = 0.0;
out1 = 0.0;
out2 = 0.0;
out3 = 0.0;
out4 = 0.0;

frequency = 1000.0;
sampleRate = 44100.0;
tenthResonance = 1.0;

% linFreq 0-1 maps to 0-half the sampling rate
% radians = (5000.0 * kTwoPi) / 44100.;
fNormalizedToHalfNyquist = frequency * 4.0 / sampleRate;

IR = double (1 : 64);

for i = 1:64

	if (i==1)
		x = 1.0;
	else
		x = 0.0;
	endif

	%% source: http://musicdsp.org/archive.php?classid=3#26
	f = fNormalizedToHalfNyquist * 1.4716;
	fb = tenthResonance * (1.0 - 0.4 * f * f);
	in0 = x - (out4 * fb);
	in0 = in0 * (0.35013 * (f*f)*(f*f));
	out1 = in0 + 0.3 * in1 + (1 - f) * out1; % Pole 1
	in1  = in0;
	out2 = out1 + 0.3 * in2 + (1 - f) * out2;  % Pole 2
	in2  = out1;
	out3 = out2 + 0.3 * in3 + (1 - f) * out3;  % Pole 3
	in3  = out2;
	out4 = out3 + 0.3 * in4 + (1 - f) * out4;  % Pole 4
	in4  = out3;
	IR(i) = out4;
	
endfor

save expectedIR.mat IR