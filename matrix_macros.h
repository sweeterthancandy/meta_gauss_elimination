#ifdef _MSC_VER
#pragma once
#endif
#ifndef MATRIX_MACROS_H
#define MATRIX_MACROS_H

#define MAKE_MATRIX_2_X_3(A,B,C,D,E,F) \
	type_list<int_type<A>, \
		type_list<int_type<B>, \
			type_list<int_type<C>, \
				type_list<int_type<D>, \
					type_list<int_type<E>, \
						type_list<int_type<F>,null_type> > > > > >

#define MAKE_MATRIX_3_X_4(A,B,C,D,E,F,G,H,I,J,K,L) \
	type_list<int_type<A>, \
		type_list<int_type<B>, \
			type_list<int_type<C>, \
				type_list<int_type<D>, \
					type_list<int_type<E>, \
						type_list<int_type<F>, \
							type_list<int_type<G>, \
								type_list<int_type<H>, \
									type_list<int_type<I>, \
										type_list<int_type<J>, \
											type_list<int_type<K>, \
												type_list<int_type<L>,null_type \
												> \
											> \
										> \
									> \
								> \
							> \
						> \
					> \
				> \
			> \
		> \
	>

#define MAKE_NN_MATRIX_3_X_4(A,B,C,D,E,F,G,H,I,J,K,L) \
	type_list<number_node<A>, \
		type_list<number_node<B>, \
			type_list<number_node<C>, \
				type_list<number_node<D>, \
					type_list<number_node<E>, \
						type_list<number_node<F>, \
							type_list<number_node<G>, \
								type_list<number_node<H>, \
									type_list<number_node<I>, \
										type_list<number_node<J>, \
											type_list<number_node<K>, \
												type_list<number_node<L>,null_type \
												> \
											> \
										> \
									> \
								> \
							> \
						> \
					> \
				> \
			> \
		> \
	>

#define MAKE_T_MATRIX_3_X_4(A,B,C,D,E,F,G,H,I,J,K,L) \
	type_list<A, \
		type_list<B, \
			type_list<C, \
				type_list<D, \
					type_list<E, \
						type_list<F, \
							type_list<G, \
								type_list<H, \
									type_list<I, \
										type_list<J, \
											type_list<K, \
												type_list<L,null_type \
												> \
											> \
										> \
									> \
								> \
							> \
						> \
					> \
				> \
			> \
		> \
	>

#define MAKE_R_MATRIX_3_X_4(A,B,C,D,E,F,G,H,I,J,K,L) \
	type_list<number_node<rational_type<A> >, \
		type_list<number_node<rational_type<B> >, \
			type_list<number_node<rational_type<C> >, \
				type_list<number_node<rational_type<D> >, \
					type_list<number_node<rational_type<E> >, \
						type_list<number_node<rational_type<F> >, \
							type_list<number_node<rational_type<G> >, \
								type_list<number_node<rational_type<H> >, \
									type_list<number_node<rational_type<I> >, \
										type_list<number_node<rational_type<J> >, \
											type_list<number_node<rational_type<K> >, \
												type_list<number_node<rational_type<L> >,null_type \
												> \
											> \
										> \
									> \
								> \
							> \
						> \
					> \
				> \
			> \
		> \
	>

#define MAKE_MATRIX_4_X_5(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T) \
	 type_list<int_type<A>, \
		type_list<int_type<B>, \
			type_list<int_type<C>, \
				type_list<int_type<D>, \
					type_list<int_type<E>,   \
						type_list<int_type<F>, \
							type_list<int_type<G>, \
								type_list<int_type<H>, \
									type_list<int_type<I>, \
										type_list<int_type<J>, \
											type_list<int_type<K>, \
												type_list<int_type<L>, \
													type_list<int_type<M>, \
														type_list<int_type<N> , \
															type_list<int_type<O> , \
																type_list<int_type<P> , \
																	type_list<int_type<Q> , \
																		type_list<int_type<R> , \
																			type_list<int_type<S> , \
																				type_list<int_type<T> ,null_type \
																				> \
																			> \
																		> \
																	> \
																> \
															> \
														> \
													> \
												> \
											> \
										> \
									> \
								> \
							> \
						> \
					> \
				> \
			> \
		> \
	>

#endif
