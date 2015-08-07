

debug:
	cd examples/simple; make

test:
	cd tests/CircularStorage; make test
	cd tests/Dcblocker; make test
	cd tests/LowpassFourPole; make test
	cd tests/LowpassOnePole; make test
	cd tests/SampleBundle; make test
	cd tests/UnitImpulse; make test
