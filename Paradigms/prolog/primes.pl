% support functions
	less(A, B) :-
			A < B.
	order([H]).
	order([H1, H2 | T]) :- H1 =< H2.
	dv(X, N) :- (X mod N) =:= 0.
% \support functions

% precalc
	comp_precalc(1).
	set(R, X, MAX) :- R < MAX,
			assert(comp_precalc(R)),
			NR is R + X,
			set(NR, X, MAX).
	
	check(X, N) :- N > 1, N1 is N - 1,
			check(X, N1).
	check(X, N) :- N > 1,
			dv(X, N).
	
	next(Z, Y) :- not(comp_precalc(Z)),
			Y is Z, !.
	next(Z, Y) :- 
			Z1 is Z + 1,
			next(Z1, Y).
	
	sieve(T, MX) :- SQT is T * T, SQT < MX,
			not(set(SQT, T, MX)),
			NT is T + 1,
			next(NT, NNT),
			sieve(NNT, MX).
	
	init(X) :- sieve(2, X).
	
	min(N, X, ANS) :- dv(N, X), prime(X),
			ANS is X.
	min(N, X, ANS) :-
			X1 is X + 1,
			min(N, X1, ANS).
% \precalc

% main part
	prime(N) :- not comp_precalc(N), !.
	composite(N) :- N > 2, not prime(N).

	prime_divisors(1, []).
	prime_divisors(N, DIVS) :- integer(N), N > 1,
			inner_divisors(N, DIVS).
	prime_divisors(N, DIVS) :- not(integer(N)), quicksort(DIVS, less, DIVS), length(DIVS, L), L =\= 0,
			inner_list(N, DIVS).

	inner_divisors(N, [N]) :- prime(N), !.
	inner_divisors(N, [H | T]) :-
		N > 1,
		min(N, 2, H),
		N1 is N / H,
		inner_divisors(N1, T),
		order([H | T]), !.
		
	inner_list(N, []) :- 
				N is 1.
	inner_list(N, [H | T]) :-
				inner_list(NN, T),
				N is NN * H.
% \main part