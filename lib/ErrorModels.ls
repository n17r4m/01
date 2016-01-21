


class ErrorModel
	constructor: (@e = 0.0001) -> 
		# Error probability is #{@e}
		
	hasError: -> 0


class IndependantErrorModel extends ErrorModel
	constructor: (@e) ->
		# Using Independant Error Model
		super(@e)
		
	hasError: -> Math.random() <= @e


class BurstErrorModel extends ErrorModel
	constructor: (@e, @B = 50, @N = 5000) ->
		# Using Burst Error Model
		# Burst length is #{B} and non-burst length is #{@N}
		super(@e)
		
	hasError: ->
		@e = @e * (@N + @B) / @B
		Math.random() <= @e


exports.IndependantErrorModel = IndependantErrorModel;
exports.BurstErrorModel = BurstErrorModel
exports.NullErrorModel = ErrorModel
