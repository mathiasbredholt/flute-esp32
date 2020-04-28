import("stdfaust.lib");

freq = nentry("freq",440,20,20000,0.01) : si.smoo;
gain = nentry("gain",1,0,1,0.01) : si.smoo;

lfo = os.sawtooth(1) * 100 + 250;

process = os.sawtooth(lfo) * gain * 0.2 : fi.lowpass(2, 500) : ef.echo(1, 0.2, 0.6);
