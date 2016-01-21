#! /usr/bin/env lsc

Simulator = require("./lib/Simulator")

if not module.parent
	
	# Simulator started, reading command-line arguments
	
	commandLineArgs = require('command-line-args');
	cli = commandLineArgs([
		{ name: 'error_model', alias: 'M', type: String, defaultValue: 'B' }
		{ name: 'burst_length', alias: 'B', type: Number, defaultValue: 50 }
		{ name: 'non_burst_length', alias: 'N', type: Number, defaultValue: 5000 }
		{ name: 'feedback_time', alias: 'A', type: Number, defaultValue: 50 }
		{ name: 'blocks', alias: 'K', type: Number, defaultValue: 1 }
		{ name: 'frame_size', alias: 'F', type: Number, defaultValue: 4000 }
		{ name: 'error', alias: 'e', type: Number, defaultValue: 0.0001 }
		{ name: 'time', alias: 'R', type: Number, defaultValue: 5000000 }
		{ name: 'runs', alias: 'T', type: Number, defaultValue: 5 }
		{ name: 'help', alias: 'h', type: Boolean }
	])
	o = cli.parse()
	
	
	if o.help
		console.info cli.getUsage();
	
	else
		
		if o.error_model isnt "B" then o.burst_length = 0 || o.non_burst_length = 0;
		
		console.info "#{o.error_model} #{o.feedback_time} #{o.blocks} #{o.frame_size} #{o.error} #{o.burst_length} #{o.non_burst_length} #{o.runs}";
		
		results = []
		
		run = o.runs + 1; while --run
			results.push (new Simulator(o)).run()
		
		#todo: Average results and calculate confidence intervals
		console.info results

else
	
	# Simulator initilized through `require`
	exports = module.exports = Simulator;

