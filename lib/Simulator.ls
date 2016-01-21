ErrorModels = require("./ErrorModels")

class Simulator
	(p) ->
		@M = switch p.error_model
			when "I" then new ErrorModels.IndependantErrorModel(p.error)
			when "B" then new ErrorModels.BurstErrorModel(p.error, p.burst_length, p.non_burst_length)
			else new ErrorModels.NullErrorModel()
		@A = if p.feedback_time? then p.feedback_time else 50
		@K = if p.blocks? then p.blocks else 1
		@F = if p.frames? then p.frames else 4000
		@R = if p.time? then p.time else 5000000
		
		@time = @R
		
	run: -> 
		frames = {correct: 0, total: 0}
		
		# todo: simulate! 
		# while (@time > @A * 2) ?
		
		{
			frames
			throughput: 0 #todo: calculate: (frames * numSends) ?
		}
		
	

exports = module.exports = Simulator
