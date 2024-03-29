/*
 * graphtheory.h
 *
 * (c) 2018 Luka Marohnić
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef GRAPHTHEORY_H
#define GRAPHTHEORY_H
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "first.h"
#include "graphe.h"

#ifndef NO_NAMESPACE_GIAC
namespace giac {
#endif // ndef NO_NAMESPACE_GIAC

enum gt_error_code {
    _GT_ERR_UNKNOWN = 0,
    _GT_ERR_NOT_A_GRAPH = 1,
    _GT_ERR_WEIGHTED_GRAPH_REQUIRED = 2,
    _GT_ERR_UNWEIGHTED_GRAPH_REQUIRED = 3,
    _GT_ERR_DIRECTED_GRAPH_REQUIRED = 4,
    _GT_ERR_UNDIRECTED_GRAPH_REQUIRED = 5,
    _GT_ERR_INVALID_EDGE = 6,
    _GT_ERR_INVALID_EDGE_ARC_MIX = 7,
    _GT_ERR_MATRIX_NOT_SYMMETRIC = 8,
    _GT_ERR_READING_FAILED = 9,
    _GT_ERR_EDGE_NOT_FOUND = 10,
    _GT_ERR_VERTEX_NOT_FOUND = 11,
    _GT_ERR_NOT_A_TREE=12,
    _GT_ERR_INVALID_NUMBER_OF_ROOTS=13,
    _GT_ERR_INVALID_ROOT=14,
    _GT_ERR_NOT_PLANAR=15,
    _GT_ERR_CONNECTED_GRAPH_REQUIRED=16,
    _GT_ERR_INVALID_DRAWING_METHOD=17,
    _GT_ERR_NOT_A_CYCLE=18,
    _GT_ERR_CYCLE_NOT_FOUND=19,
    _GT_ERR_NAME_NOT_RECOGNIZED=20,
    _GT_ERR_NOT_A_SUBGRAPH=21,
    _GT_ERR_GRAPH_IS_NULL=22,
    _GT_ERR_TAGVALUE_PAIR_EXPECTED=23,
    _GT_ERR_NOT_A_GRAPHIC_SEQUENCE=24,
    _GT_ERR_NOT_ACYCLIC_GRAPH=25,
    _GT_ERR_BICONNECTED_GRAPH_REQUIRED=26,
    _GT_ERR_NOT_BIPARTITE=27,
    _GT_ERR_WRONG_NUMBER_OF_ARGS=28,
    _GT_ERR_POSITIVE_INTEGER_REQUIRED=29,
    _GT_ERR_BAD_VERTICES=30
};

enum distribution_type {
    _DISTR_UNIFORM,
    _DISTR_POISSON,
    _DISTR_EXPONENTIAL,
    _DISTR_GEOMETRIC,
    _DISTR_NORMAL,
    _DISTR_FISHER,
    _DISTR_CHISQUARE,
    _DISTR_CAUCHY,
    _DISTR_STUDENT,
    _DISTR_MULTINOMIAL,
    _DISTR_BINOMIAL,
    _DISTR_GAMMA,
    _DISTR_BETA,
    _DISTR_WEIBULL,
    _DISTR_DISCRETE
};

bool is_graphe(const gen &g,std::string &disp_out,GIAC_CONTEXT);

// GRAPH THEORY GIAC COMMANDS

gen _graph(const gen &g,GIAC_CONTEXT);
gen _digraph(const gen &g,GIAC_CONTEXT);
gen _export_graph(const gen &g,GIAC_CONTEXT);
gen _import_graph(const gen &g,GIAC_CONTEXT);
gen _trail(const gen &g,GIAC_CONTEXT);
gen _trail2edges(const gen &g,GIAC_CONTEXT);
gen _draw_graph(const gen &g,GIAC_CONTEXT);
gen _graph_complement(const gen &g,GIAC_CONTEXT);
gen _induced_subgraph(const gen &g,GIAC_CONTEXT);
gen _make_directed(const gen &g,GIAC_CONTEXT);
gen _seidel_switch(const gen &g,GIAC_CONTEXT);
gen _complete_graph(const gen &g,GIAC_CONTEXT);
gen _make_weighted(const gen &g,GIAC_CONTEXT);
gen _subgraph(const gen &g,GIAC_CONTEXT);
gen _underlying_graph(const gen &g,GIAC_CONTEXT);
gen _cycle_graph(const gen &g,GIAC_CONTEXT);
gen _path_graph(const gen &g,GIAC_CONTEXT);
gen _lcf_graph(const gen &g,GIAC_CONTEXT);
gen _add_arc(const gen &g,GIAC_CONTEXT);
gen _add_edge(const gen &g,GIAC_CONTEXT);
gen _add_vertex(const gen &g,GIAC_CONTEXT);
gen _delete_arc(const gen &g,GIAC_CONTEXT);
gen _delete_edge(const gen &g,GIAC_CONTEXT);
gen _delete_vertex(const gen &g,GIAC_CONTEXT);
gen _contract_edge(const gen &g,GIAC_CONTEXT);
gen _set_graph_attribute(const gen &g,GIAC_CONTEXT);
gen _get_graph_attribute(const gen &g,GIAC_CONTEXT);
gen _discard_graph_attribute(const gen &g,GIAC_CONTEXT);
gen _list_graph_attributes(const gen &g,GIAC_CONTEXT);
gen _set_vertex_attribute(const gen &g,GIAC_CONTEXT);
gen _get_vertex_attribute(const gen &g,GIAC_CONTEXT);
gen _discard_vertex_attribute(const gen &g,GIAC_CONTEXT);
gen _list_vertex_attributes(const gen &g,GIAC_CONTEXT);
gen _set_node_attribute(const gen &g,GIAC_CONTEXT);
gen _get_node_attribute(const gen &g,GIAC_CONTEXT);
gen _discard_node_attribute(const gen &g,GIAC_CONTEXT);
gen _list_edge_attributes(const gen &g,GIAC_CONTEXT);
gen _adjacency_matrix(const gen &g,GIAC_CONTEXT);
gen _incidence_matrix(const gen &g,GIAC_CONTEXT);
gen _biconnected_components(const gen &g,GIAC_CONTEXT);
gen _connected_components(const gen &g,GIAC_CONTEXT);
gen _departures(const gen &g,GIAC_CONTEXT);
gen _incident_edges(const gen &g,GIAC_CONTEXT);
gen _number_of_triangles(const gen &g,GIAC_CONTEXT);
gen _is_connected(const gen &g,GIAC_CONTEXT);
gen _is_biconnected(const gen &g,GIAC_CONTEXT);
gen _is_triconnected(const gen &g,GIAC_CONTEXT);
gen _is_weighted(const gen &g,GIAC_CONTEXT);
gen _is_forest(const gen &g,GIAC_CONTEXT);
gen _is_tournament(const gen &g,GIAC_CONTEXT);
gen _is_planar(const gen &g,GIAC_CONTEXT);
gen _is_tree(const gen &g,GIAC_CONTEXT);
gen _tree_height(const gen &g,GIAC_CONTEXT);
gen _maximum_matching(const gen &g,GIAC_CONTEXT);
gen _bipartite_matching(const gen &g,GIAC_CONTEXT);
gen _number_of_edges(const gen &g,GIAC_CONTEXT);
gen _edges(const gen &g,GIAC_CONTEXT);
gen _has_arc(const gen &g,GIAC_CONTEXT);
gen _arrivals(const gen &g,GIAC_CONTEXT);
gen _articulation_points(const gen &g,GIAC_CONTEXT);
gen _vertex_in_degree(const gen &g,GIAC_CONTEXT);
gen _vertex_out_degree(const gen &g,GIAC_CONTEXT);
gen _vertex_degree(const gen &g,GIAC_CONTEXT);
gen _get_edge_weight(const gen &g,GIAC_CONTEXT);
gen _set_edge_weight(const gen &g,GIAC_CONTEXT);
gen _has_edge(const gen &g,GIAC_CONTEXT);
gen _is_directed(const gen &g,GIAC_CONTEXT);
gen _minimum_degree(const gen &g,GIAC_CONTEXT);
gen _maximum_degree(const gen &g,GIAC_CONTEXT);
gen _is_regular(const gen &g,GIAC_CONTEXT);
gen _is_strongly_regular(const gen &g,GIAC_CONTEXT);
gen _neighbors(const gen &g,GIAC_CONTEXT);
gen _number_of_vertices(const gen &g,GIAC_CONTEXT);
gen _graph_vertices(const gen &g,GIAC_CONTEXT);
gen _relabel_vertices(const gen &g,GIAC_CONTEXT);
gen _permute_vertices(const gen &g,GIAC_CONTEXT);
gen _isomorphic_copy(const gen &g,GIAC_CONTEXT);
gen _weight_matrix(const gen &g,GIAC_CONTEXT);
gen _hypercube_graph(const gen &g,GIAC_CONTEXT);
gen _sierpinski_graph(const gen &g,GIAC_CONTEXT);
gen _petersen_graph(const gen &g,GIAC_CONTEXT);
gen _complete_binary_tree(const gen &g,GIAC_CONTEXT);
gen _complete_kary_tree(const gen &g,GIAC_CONTEXT);
gen _prism_graph(const gen &g,GIAC_CONTEXT);
gen _antiprism_graph(const gen &g,GIAC_CONTEXT);
gen _star_graph(const gen &g,GIAC_CONTEXT);
gen _grid_graph(const gen &g,GIAC_CONTEXT);
gen _torus_grid_graph(const gen &g,GIAC_CONTEXT);
gen _web_graph(const gen &g,GIAC_CONTEXT);
gen _wheel_graph(const gen &g,GIAC_CONTEXT);
gen _kneser_graph(const gen &g,GIAC_CONTEXT);
gen _odd_graph(const gen &g,GIAC_CONTEXT);
gen _random_graph(const gen &g,GIAC_CONTEXT);
gen _random_digraph(const gen &g,GIAC_CONTEXT);
gen _random_regular_graph(const gen &g,GIAC_CONTEXT);
gen _random_sequence_graph(const gen &g,GIAC_CONTEXT);
gen _random_bipartite_graph(const gen &g,GIAC_CONTEXT);
gen _random_tournament(const gen &g,GIAC_CONTEXT);
gen _random_tree(const gen &g,GIAC_CONTEXT);
gen _random_planar_graph(const gen &g,GIAC_CONTEXT);
gen _assign_edge_weights(const gen &g,GIAC_CONTEXT);
gen _cartesian_product(const gen &g,GIAC_CONTEXT);
gen _tensor_product(const gen &g,GIAC_CONTEXT);
gen _is_eulerian(const gen &g,GIAC_CONTEXT);
gen _highlight_vertex(const gen &g,GIAC_CONTEXT);
gen _highlight_edges(const gen &g,GIAC_CONTEXT);
gen _highlight_subgraph(const gen &g,GIAC_CONTEXT);
gen _highlight_trail(const gen &g,GIAC_CONTEXT);
gen _disjoint_union(const gen &g,GIAC_CONTEXT);
gen _graph_union(const gen &g,GIAC_CONTEXT);
gen _graph_join(const gen &g,GIAC_CONTEXT);
gen _graph_equal(const gen &g,GIAC_CONTEXT);
gen _reverse_graph(const gen &g,GIAC_CONTEXT);
gen _interval_graph(const gen &g,GIAC_CONTEXT);
gen _subdivide_edges(const gen &g,GIAC_CONTEXT);
gen _graph_power(const gen &g,GIAC_CONTEXT);
gen _vertex_distance(const gen &g,GIAC_CONTEXT);
gen _shortest_path(const gen &g,GIAC_CONTEXT);
gen _dijkstra(const gen &g,GIAC_CONTEXT);
gen _bellman_ford(const gen &g,GIAC_CONTEXT);
gen _allpairs_distance(const gen &g,GIAC_CONTEXT);
gen _graph_diameter(const gen &g,GIAC_CONTEXT);
gen _is_clique(const gen &g,GIAC_CONTEXT);
gen _maximum_clique(const gen &g,GIAC_CONTEXT);
gen _clique_number(const gen &g,GIAC_CONTEXT);
gen _clique_cover(const gen &g,GIAC_CONTEXT);
gen _clique_cover_number(const gen &g,GIAC_CONTEXT);
gen _chromatic_number(const gen &g,GIAC_CONTEXT);
gen _maximum_independent_set(const gen &g,GIAC_CONTEXT);
gen _independence_number(const gen &g,GIAC_CONTEXT);
gen _strongly_connected_components(const gen &g,GIAC_CONTEXT);
gen _is_strongly_connected(const gen &g,GIAC_CONTEXT);
gen _condensation(const gen &g,GIAC_CONTEXT);
gen _degree_sequence(const gen &g,GIAC_CONTEXT);
gen _is_graphic_sequence(const gen &g,GIAC_CONTEXT);
gen _sequence_graph(const gen &g,GIAC_CONTEXT);
gen _girth(const gen &g,GIAC_CONTEXT);
gen _odd_girth(const gen &g,GIAC_CONTEXT);
gen _topologic_sort(const gen &g,GIAC_CONTEXT);
gen _is_acyclic(const gen &g,GIAC_CONTEXT);
gen _is_arborescence(const gen &g,GIAC_CONTEXT);
gen _graph_spectrum(const gen &g,GIAC_CONTEXT);
gen _graph_charpoly(const gen &g,GIAC_CONTEXT);
gen _seidel_spectrum(const gen &g,GIAC_CONTEXT);
gen _is_integer_graph(const gen &g,GIAC_CONTEXT);
gen _spanning_tree(const gen &g,GIAC_CONTEXT);
gen _number_of_spanning_trees(const gen &g,GIAC_CONTEXT);
gen _minimal_spanning_tree(const gen &g,GIAC_CONTEXT);
gen _graph_rank(const gen &g,GIAC_CONTEXT);
gen _lowest_common_ancestor(const gen &g,GIAC_CONTEXT);
gen _st_ordering(const gen &g,GIAC_CONTEXT);
gen _is_bipartite(const gen &g,GIAC_CONTEXT);
gen _greedy_color(const gen &g,GIAC_CONTEXT);
gen _is_vertex_colorable(const gen &g,GIAC_CONTEXT);
gen _plane_dual(const gen &g,GIAC_CONTEXT);
gen _set_vertex_positions(const gen &g,GIAC_CONTEXT);
gen _clique_stats(const gen &g,GIAC_CONTEXT);
gen _minimal_vertex_coloring(const gen &g,GIAC_CONTEXT);
gen _transitive_closure(const gen &g,GIAC_CONTEXT);
gen _line_graph(const gen &g,GIAC_CONTEXT);
gen _is_isomorphic(const gen &g,GIAC_CONTEXT);
gen _graph_automorphisms(const gen &g,GIAC_CONTEXT);
gen _canonical_labeling(const gen &g,GIAC_CONTEXT);
gen _minimal_edge_coloring(const gen &g,GIAC_CONTEXT);
gen _chromatic_index(const gen &g,GIAC_CONTEXT);
gen _is_hamiltonian(const gen &g,GIAC_CONTEXT);
gen _traveling_salesman(const gen &g,GIAC_CONTEXT);
gen _maxflow(const gen &g,GIAC_CONTEXT);
gen _minimum_cut(const gen &g,GIAC_CONTEXT);
gen _is_cut_set(const gen &g,GIAC_CONTEXT);
gen _is_network(const gen &g,GIAC_CONTEXT);
gen _random_network(const gen &g,GIAC_CONTEXT);
gen _tutte_polynomial(const gen &g,GIAC_CONTEXT);
gen _chromatic_polynomial(const gen &g,GIAC_CONTEXT);
gen _flow_polynomial(const gen &g,GIAC_CONTEXT);
gen _reliability_polynomial(const gen &g,GIAC_CONTEXT);
gen _laplacian_matrix(const gen &g,GIAC_CONTEXT);
gen _fundamental_cycle(const gen &g,GIAC_CONTEXT);
gen _cycle_basis(const gen &g,GIAC_CONTEXT);
gen _mycielski(const gen &g,GIAC_CONTEXT);
gen _clustering_coefficient(const gen &g,GIAC_CONTEXT);
gen _network_transitivity(const gen &g,GIAC_CONTEXT);
gen _two_edge_connected_components(const gen &g,GIAC_CONTEXT);
gen _is_two_edge_connected(const gen &g,GIAC_CONTEXT);
gen _edge_connectivity(const gen &g,GIAC_CONTEXT);
gen _vertex_connectivity(const gen &g,GIAC_CONTEXT);
gen _tonnetz(const gen &g,GIAC_CONTEXT);
gen _truncate_graph(const gen &g,GIAC_CONTEXT);
gen _find_cycles(const gen &g,GIAC_CONTEXT);
gen _kspaths(const gen &g,GIAC_CONTEXT);
gen _degree_centrality(const gen &g,GIAC_CONTEXT);
gen _betweenness_centrality(const gen &g,GIAC_CONTEXT);
gen _closeness_centrality(const gen &g,GIAC_CONTEXT);
gen _katz_centrality(const gen &g,GIAC_CONTEXT);
gen _information_centrality(const gen &g,GIAC_CONTEXT);
gen _harmonic_centrality(const gen &g,GIAC_CONTEXT);
gen _is_split_graph(const gen &g,GIAC_CONTEXT);
gen _contract_subgraph(const gen &g,GIAC_CONTEXT);
gen _greedy_clique(const gen &g,GIAC_CONTEXT);
gen _greedy_independent_set(const gen &g,GIAC_CONTEXT);
gen _minimum_vertex_cover(const gen &g,GIAC_CONTEXT);
gen _find_vertex_cover(const gen &g,GIAC_CONTEXT);
gen _vertex_cover_number(const gen &g,GIAC_CONTEXT);

// GENERAL GIAC COMMANDS

gen _foldl(const gen &g,GIAC_CONTEXT);
gen _foldr(const gen &g,GIAC_CONTEXT);
gen _randvar(const gen &g,GIAC_CONTEXT);
gen _icomp(const gen &g,GIAC_CONTEXT);

// FUNCTION POINTERS

extern const unary_function_ptr * const at_trail;

#ifndef NO_NAMESPACE_GIAC
} // namespace giac
#endif // ndef NO_NAMESPACE_GIAC
#endif // GRAPHTHEORY_H
