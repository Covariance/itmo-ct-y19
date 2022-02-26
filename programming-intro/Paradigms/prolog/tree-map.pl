% user-called functions

	map_build([], leaf).
	map_build([(K, V) | T], RES) :-
			map_build(T, NRES),
			map_put(NRES, K, V, RES).

	map_put(TREE, K, V, NTREE) :-
			rand_int(1000000007, H),
			NNODE = node(K, V, H, leaf, leaf, 1),
			insert(TREE, NNODE, NTREE).

	map_remove(TREE, K, NTREE) :-
			tri_split(TREE, K, L, DELETED, R),
			merge(L, R, NTREE).

	map_get(node(K, V, _, _, _, _), K, V).
	map_get(node(CURK, CURV, _, L, R, _), K, V) :- K < CURK,
			map_get(L, K, V).
	map_get(node(CURK, CURV, _, L, R, _), K, V) :- not(K < CURK),
			map_get(R, K, V).

	% [FLOOR; CEILING)
	map_submapSize(TREE, FLOOR, CEILING, 0)    :- FLOOR >= CEILING,
	map_submapSize(TREE, FLOOR, CEILING, SIZE) :- FLOOR < CEILING,
			right_split(TREE, FLOOR, _, HALF_SPLITTED),
			right_split(HALF_SPLITTED, CEILING, SEGMENT, _),
			tree_size(SEGMENT, SIZE).
	
% \user-called functions

% insides

	% size(<current tree>, <tree size>)
	tree_size(leaf, 0).
	tree_size(node(_, _, _, _, _, SIZE), SIZE).

	% insert(<current tree>, <node to insert>, <resulting tree>)
	insert(TREE, NNODE, NTREE) :- 
			NNODE = node(K, _, _, _, _, _),
			tri_split(TREE, K, L, DELETED, R),
			merge(L, NNODE, HALF_JOINED),
			merge(HALF_JOINED, R, NTREE).
	
	% tri_split(<current tree>, <key to split by>, <less than key>, <equal to key>, <greater than key>)
	tri_split(TREE, K, L, M, R) :-
			right_split(TREE, K, L, HALF_SPLITTED),
			left_split(HALF_SPLITTED, K, M, R).

	% split(<splitting predicate>, <current tree>, <key to split by>, <lesser or equal to key>, <greater than key>)
	split(_, leaf, _, leaf, leaf) :- !.
	split(PRED, node(K, V, H, L, R, CUR_SIZE), SPLITTER, LRES, RRES) :- APP_PRED =.. [PRED, SPLITTER, K], call(APP_PRED),
			split(PRED, L, SPLITTER, NL, NR),
			tree_size(NL, SPLITTED_SIZE),
			NSIZE is CUR_SIZE - SPLITTED_SIZE,
			LRES = NL,
			RRES = node(K, V, H, NR, R, NSIZE).
	split(PRED, node(K, V, H, L, R, CUR_SIZE), SPLITTER, LRES, RRES) :- APP_PRED =.. [PRED, SPLITTER, K], not(call(APP_PRED)),
			split(PRED, R, SPLITTER, NL, NR),
			tree_size(NR, SPLITTED_SIZE),
			NSIZE is CUR_SIZE - SPLITTED_SIZE,
			LRES = node(K, V, H, L, NL, NSIZE),
			RRES = NR.

	% predicates for split
	le(A, B) :- A < B.
	leq(A, B) :- A =< B.

	% split specifications
	left_split(TREE, SPLITTER, LRES, RRES) :- split(le, TREE, SPLITTER, LRES, RRES).
	right_split(TREE, SPLITTER, LRES, RRES) :- split(leq, TREE, SPLITTER, LRES, RRES).

	% merge(<left part>, <right part>, <new tree>)
	merge(L, leaf, L) :- !.
	merge(leaf, R, R) :- !.
	merge(node(KL, VL, HL, LL, LR, LSIZE), R, NTREE) :-
 R = node(_, _, HR, _, _, RSIZE),
 HL > HR,
			merge(LR, R, HALF_MERGED),
			NSIZE is LSIZE + RSIZE,
			NTREE = node(KL, VL, HL, LL, HALF_MERGED, NSIZE).
	merge(L, node(KR, VR, HR, RL, RR, RSIZE), NTREE) :-
 L = node(_, _, HL, _, _, LSIZE), not(HL > HR),
			merge(L, RL, HALF_MERGED),
			NSIZE is LSIZE + RSIZE,
			NTREE = node(KR, VR, HR, HALF_MERGED, RR, NSIZE).
				
% \insides