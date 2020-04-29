// import("stdfaust.lib");
//
// freq = nentry("freq",440,20,20000,0.01) : si.smoo;
// gain = nentry("gain",1,0,1,0.01) : si.smoo;
//
// lfo = os.sawtooth(1) * 100 + 250;
//
// process = os.sawtooth(freq) * gain * 0.5 : fi.lowpass(2, 1000);


declare name "FluteMIDI";
declare description "Simple MIDI-controllable flute physical model with physical parameters.";
declare license "MIT";
declare copyright "(c)Romain Michon, CCRMA (Stanford University), GRAME";

import("stdfaust.lib");

process = pm.flute_ui_MIDI <: _,_;
