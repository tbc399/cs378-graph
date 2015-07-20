// --------------------------------
// projects/g++/graph/TestGraph.c++
// Copyright (C) 2015
// Glenn P. Downing
// --------------------------------

// --------
// includes
// --------

#include <iostream> // cout, endl
#include <iterator> // ostream_iterator
#include <sstream>  // ostringstream
#include <utility>  // pair

#include "boost/graph/adjacency_list.hpp"  // adjacency_list
#include "boost/graph/topological_sort.hpp"// topological_sort

#include "gtest/gtest.h"

#include "Graph.h"

using namespace std;

using testing::Test;
using testing::Types;

// ---------
// TestGraph
// ---------

template <typename G>
struct TestGraph : Test {
    // --------
    // typedefs
    // --------

    typedef          G                     graph_type;
    typedef typename G::vertex_descriptor  vertex_descriptor;
    typedef typename G::edge_descriptor    edge_descriptor;
    typedef typename G::vertex_iterator    vertex_iterator;
    typedef typename G::edge_iterator      edge_iterator;
    typedef typename G::adjacency_iterator adjacency_iterator;
    typedef typename G::vertices_size_type vertices_size_type;
    typedef typename G::edges_size_type    edges_size_type;
};

// directed, sparse, unweighted
// possibly connected
// possibly cyclic
typedef Types<
            boost::adjacency_list<boost::setS, boost::vecS, boost::directedS>,
            Graph>
        graph_types;
/*
typedef Types<boost::adjacency_list<boost::setS, boost::vecS, boost::directedS>>
        graph_types;
*/
TYPED_TEST_CASE(TestGraph, graph_types);

// --------
// add_edge
// --------

TYPED_TEST(TestGraph, add_edge_1) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    
    graph_type g;
    vertex_descriptor v1 = 0;
    vertex_descriptor v2 = 1;
    auto p = add_edge(v1, v2, g);
    auto v3 = target(p.first, g);
    auto v4 = source(p.first, g);
    ASSERT_EQ(v1, v4);
    ASSERT_EQ(v2, v3);
    ASSERT_TRUE(p.second);
}

TYPED_TEST(TestGraph, add_edge_2) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    
    graph_type g;
    vertex_descriptor v1 = 0;
    vertex_descriptor v2 = 1;
    auto p1 = add_edge(v1, v2, g);
    auto p2 = add_edge(v1, v2, g);
    auto v3 = target(p1.first, g);
    auto v4 = source(p1.first, g);
    ASSERT_EQ(v1, v4);
    ASSERT_EQ(v2, v3);
    ASSERT_FALSE(p2.second);
    ASSERT_EQ(p1.first, p2.first);
}

TYPED_TEST(TestGraph, add_edge_3) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    
    graph_type g;
    vertex_descriptor v1 = 0;
    vertex_descriptor v2 = 1;
    auto p1 = add_edge(v1, v2, g);
    auto p2 = add_edge(v2, v1, g);
    auto vv1 = source(p1.first, g);
    auto vv2 = target(p1.first, g);
    auto vv3 = source(p2.first, g);
    auto vv4 = target(p2.first, g);
    ASSERT_EQ(v1, vv1);
    ASSERT_EQ(v2, vv2);
    ASSERT_EQ(v2, vv3);
    ASSERT_EQ(v1, vv4);
    ASSERT_NE(p2.first, p1.first);
}

// ----------
// add_vertex
// ----------

TYPED_TEST(TestGraph, add_vertex_1) {
    typedef typename TestFixture::graph_type         graph_type;
    
    graph_type g;
    
    add_vertex(g);
    ASSERT_EQ(1, num_vertices(g));
}

TYPED_TEST(TestGraph, add_vertex_2) {
    typedef typename TestFixture::graph_type         graph_type;
    
    graph_type g;
    
    auto v1 = add_vertex(g);
    auto v2 = add_vertex(g);
    ASSERT_EQ(2, num_vertices(g));
    ASSERT_NE(v1, v2);
}

TYPED_TEST(TestGraph, add_vertex_3) {
    typedef typename TestFixture::graph_type         graph_type;
    
    graph_type g;
    
    add_vertex(g);
    add_vertex(g);
    add_vertex(g);
    add_vertex(g);
    add_vertex(g);
    add_vertex(g);
    add_vertex(g);
    add_vertex(g);
    add_vertex(g);
    add_vertex(g);
    add_vertex(g);
    add_vertex(g);
    ASSERT_EQ(12, num_vertices(g));
}

// -----------------
// adjacent_vertices
// -----------------

TYPED_TEST(TestGraph, adjacent_vertices_1) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    
    graph_type g;
    vertex_descriptor u = 0;
    vertex_descriptor v = 1;
    add_edge(u, v, g);
    auto p = adjacent_vertices(u, g);
    ASSERT_EQ(p.second, ++p.first);
}

TYPED_TEST(TestGraph, adjacent_vertices_2) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    
    graph_type g;
    vertex_descriptor u = 0;
    vertex_descriptor v = 1;
    vertex_descriptor w = 2;
    add_edge(u, v, g);
    add_edge(u, w, g);
    auto p = adjacent_vertices(u, g);
    ASSERT_EQ(p.second, ++++p.first);
}

TYPED_TEST(TestGraph, adjacent_vertices_3) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    
    graph_type g;
    vertex_descriptor u = 0;
    vertex_descriptor v = 1;
    add_edge(v, u, g);
    auto p = adjacent_vertices(u, g);
    ASSERT_EQ(p.second, p.first);
}

// ----
// edge
// ----

TYPED_TEST(TestGraph, edge_1) {
    typedef typename TestFixture::graph_type         graph_type;
    
    graph_type g;
    auto u = add_vertex(g);
    auto v = add_vertex(g);
    auto p = edge(u, v, g);
    ASSERT_FALSE(p.second);
}

TYPED_TEST(TestGraph, edge_2) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    
    graph_type g;
    vertex_descriptor u = 0;
    vertex_descriptor v = 1;
    auto p1 = add_edge(u, v, g);
    auto p2 = edge(u, v, g);
    ASSERT_TRUE(p2.second);
    ASSERT_EQ(p2.first, p1.first);
}

TYPED_TEST(TestGraph, edge_3) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    
    graph_type g;
    vertex_descriptor u = 0;
    vertex_descriptor v = 1;
    vertex_descriptor w = 2;
    add_edge(u, v, g);
    add_edge(v, w, g);
    auto p = edge(u, w, g);
    ASSERT_FALSE(p.second);
}

// -----
// edges
// -----

TYPED_TEST(TestGraph, edges_1) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    
    graph_type g;
   	vertex_descriptor u = 0;
   	vertex_descriptor v = 1;
   	add_edge(u, v, g);
   	auto p = edges(g);
   	ASSERT_EQ(p.second, ++p.first);
}

TYPED_TEST(TestGraph, edges_2) {
    typedef typename TestFixture::graph_type         graph_type;
    
    graph_type g;
   	add_vertex(g);
   	add_vertex(g);
   	auto p = edges(g);
   	ASSERT_EQ(p.second, p.first);
}

TYPED_TEST(TestGraph, edges_3) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    
    graph_type g;
   	vertex_descriptor u = 0;
   	vertex_descriptor v = 1;
   	vertex_descriptor w = 2;
   	vertex_descriptor x = 3;
   	add_edge(u, v, g);
   	add_edge(v, w, g);
   	add_edge(w, x, g);
   	add_edge(x, u, g);
   	auto p = edges(g);
   	int i = 4;
   	while (i-- > 0) {
   		++p.first;
   	}
   	ASSERT_EQ(p.second, p.first);
}

// ---------
// num_edges
// ---------

TYPED_TEST(TestGraph, num_edges_1) {
    typedef typename TestFixture::graph_type         graph_type;
    
    graph_type g;
    auto u = add_vertex(g);
    auto v = add_vertex(g);
    add_edge(u, v, g);
    auto n = num_edges(g);
    ASSERT_EQ(1, n);
}

TYPED_TEST(TestGraph, num_edges_2) {
    typedef typename TestFixture::graph_type         graph_type;
    
    graph_type g;
    auto n = num_edges(g);
    ASSERT_EQ(0, n);
}

TYPED_TEST(TestGraph, num_edges_3) {
    typedef typename TestFixture::graph_type         graph_type;
    
    graph_type g;
    auto u = add_vertex(g);
    auto v = add_vertex(g);
    add_edge(u, v, g);
    add_edge(v, u, g);
    auto n = num_edges(g);
    ASSERT_EQ(2, n);
}

// ------------
// num_vertices
// ------------

TYPED_TEST(TestGraph, num_vertices_1) {
    typedef typename TestFixture::graph_type         graph_type;
    
    graph_type g;
    auto n = num_vertices(g);
    ASSERT_EQ(0, n);
}

TYPED_TEST(TestGraph, num_vertices_2) {
    typedef typename TestFixture::graph_type         graph_type;
    
    graph_type g;
    add_vertex(g);
    add_vertex(g);
    add_vertex(g);
    auto n = num_vertices(g);
    ASSERT_EQ(3, n);
}

TYPED_TEST(TestGraph, num_vertices_3) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    
    graph_type g;
    vertex_descriptor u = 0;
    vertex_descriptor v = 1;
    add_edge(u, v, g);
    auto n = num_vertices(g);
    ASSERT_EQ(2, n);
}

TYPED_TEST(TestGraph, num_vertices_4) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    
    graph_type g;
    vertex_descriptor u = 0;
    vertex_descriptor v = 1;
    add_edge(u, v, g);
    add_edge(v, u, g);
    auto n = num_vertices(g);
    ASSERT_EQ(2, n);
}

// ------
// source
// ------

TYPED_TEST(TestGraph, source_1) {
    typedef typename TestFixture::graph_type         graph_type;
    
    graph_type g;
    auto u = add_vertex(g);
    auto v = add_vertex(g);
    auto p = add_edge(u, v, g);
    auto ud = source(p.first, g);
    ASSERT_EQ(u, ud);
}

TYPED_TEST(TestGraph, source_2) {
    typedef typename TestFixture::graph_type         graph_type;
    
    graph_type g;
    auto u = add_vertex(g);
    auto v = add_vertex(g);
    auto p = add_edge(u, v, g);
    auto ud = source(p.first, g);
    ASSERT_NE(v, ud);
}

TYPED_TEST(TestGraph, source_3) {
    typedef typename TestFixture::graph_type         graph_type;
    
    graph_type g;
    auto u = add_vertex(g);
    auto v = add_vertex(g);
    auto w = add_vertex(g);
    auto p1 = add_edge(u, v, g);
    auto p2 = add_edge(v, w, g);
    auto ud = source(p1.first, g);
    auto vd = source(p2.first, g);
    ASSERT_EQ(u, ud);
    ASSERT_EQ(v, vd);
}

// ------
// target
// ------

TYPED_TEST(TestGraph, target_1) {
    typedef typename TestFixture::graph_type         graph_type;
    
    graph_type g;
    auto u = add_vertex(g);
    auto v = add_vertex(g);
    auto p = add_edge(u, v, g);
    auto vd = target(p.first, g);
    ASSERT_EQ(v, vd);
}

TYPED_TEST(TestGraph, target_2) {
    typedef typename TestFixture::graph_type         graph_type;
    
    graph_type g;
    auto u = add_vertex(g);
    auto v = add_vertex(g);
    auto p = add_edge(u, v, g);
    auto vd = target(p.first, g);
    ASSERT_NE(u, vd);
}

TYPED_TEST(TestGraph, target_3) {
    typedef typename TestFixture::graph_type         graph_type;
    
    graph_type g;
    auto u = add_vertex(g);
    auto v = add_vertex(g);
    auto w = add_vertex(g);
    auto p1 = add_edge(u, v, g);
    auto p2 = add_edge(v, w, g);
    auto vd = target(p1.first, g);
    auto wd = target(p2.first, g);
    ASSERT_EQ(v, vd);
    ASSERT_EQ(w, wd);
}

// ------
// vertex
// ------

TYPED_TEST(TestGraph, vertex_1) {
    typedef typename TestFixture::graph_type         graph_type;
    
    graph_type g;
    auto u = add_vertex(g);
    ASSERT_EQ(u, vertex(0, g));
}

TYPED_TEST(TestGraph, vertex_2) {
    typedef typename TestFixture::graph_type         graph_type;
    
    graph_type g;
    add_vertex(g);
    add_vertex(g);
    add_vertex(g);
    ASSERT_EQ(2, vertex(2, g));
}

TYPED_TEST(TestGraph, vertex_3) {
    typedef typename TestFixture::graph_type         graph_type;
    
    graph_type g;
    add_vertex(g);
    add_vertex(g);
    add_vertex(g);
    add_vertex(g);
    add_vertex(g);
    add_vertex(g);
    add_vertex(g);
    add_vertex(g);
    add_vertex(g);
    auto u = add_vertex(g);
    add_vertex(g);
    add_vertex(g);
    ASSERT_EQ(u, vertex(9, g));
}

// --------
// vertices
// --------

TYPED_TEST(TestGraph, vertices_1) {
    typedef typename TestFixture::graph_type         graph_type;
    
    graph_type g;
    auto p = vertices(g);
    ASSERT_EQ(p.first, p.second);
}

TYPED_TEST(TestGraph, vertices_2) {
    typedef typename TestFixture::graph_type         graph_type;
    
    graph_type g;
    add_vertex(g);
    add_vertex(g);
    auto p = vertices(g);
    ASSERT_EQ(p.second, ++++p.first);
}

TYPED_TEST(TestGraph, vertices_3) {
    typedef typename TestFixture::graph_type         graph_type;
    
    graph_type g;
    add_vertex(g);
    add_vertex(g);
    add_vertex(g);
    auto p = vertices(g);
    ASSERT_EQ(p.second, ++++++p.first);
}

// -----------
// constructor
// -----------

TYPED_TEST(TestGraph, constructor_1) {
    typedef typename TestFixture::graph_type         graph_type;
    
    graph_type g;
    ASSERT_EQ(0, num_vertices(g));
}

TYPED_TEST(TestGraph, constructor_2) {
    typedef typename TestFixture::graph_type         graph_type;
    
    graph_type g;
    ASSERT_EQ(0, num_edges(g));
}

// -----
// other
// -----

TYPED_TEST(TestGraph, test_vertex) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::vertices_size_type vertices_size_type;

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);

    vertex_descriptor vd = vertex(0, g);
    ASSERT_EQ(vdA, vd);

    vertices_size_type vs = num_vertices(g);
    ASSERT_EQ(1, vs);
}

TYPED_TEST(TestGraph, test_edge) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;
    typedef typename TestFixture::edges_size_type    edges_size_type;

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);

    edge_descriptor edAB = add_edge(vdA, vdB, g).first;

    pair<edge_descriptor, bool> p1 = add_edge(vdA, vdB, g);
    ASSERT_EQ(edAB,  p1.first);
    ASSERT_EQ(false, p1.second);

    pair<edge_descriptor, bool> p2 = edge(vdA, vdB, g);
    ASSERT_EQ(edAB, p2.first);
    ASSERT_EQ(true, p2.second);

    edges_size_type es = num_edges(g);
    ASSERT_EQ(1, es);

    vertex_descriptor vd1 = source(edAB, g);
    ASSERT_EQ(vdA, vd1);

    vertex_descriptor vd2 = target(edAB, g);
    ASSERT_EQ(vdB, vd2);
}

TYPED_TEST(TestGraph, test_vertices) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::vertex_iterator    vertex_iterator;

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);

    pair<vertex_iterator, vertex_iterator> p = vertices(g);
    vertex_iterator                        b = p.first;
    vertex_iterator                        e = p.second;
    if (b != e) {
        vertex_descriptor vd = *b;
        ASSERT_EQ(vdA, vd);}
    ++b;
    if (b != e) {
        vertex_descriptor vd = *b;
        ASSERT_EQ(vdB, vd);}
    ++b;
    ASSERT_EQ(e, b);
}

TYPED_TEST(TestGraph, test_edges) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;
    typedef typename TestFixture::edge_iterator      edge_iterator;

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);
    vertex_descriptor vdC = add_vertex(g);

    edge_descriptor edAB = add_edge(vdA, vdB, g).first;
    edge_descriptor edAC = add_edge(vdA, vdC, g).first;

    pair<edge_iterator, edge_iterator> p = edges(g);
    edge_iterator                      b = p.first;
    edge_iterator                      e = p.second;
    if (b != e) {
        edge_descriptor ed = *b;
        ASSERT_EQ(edAB, ed);}
    ++b;
    if (b != e) {
        edge_descriptor ed = *b;
        ASSERT_EQ(edAC, ed);}
    ++b;
    ASSERT_EQ(e, b);
}

TYPED_TEST(TestGraph, test_adjacent_vertices) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);
    vertex_descriptor vdC = add_vertex(g);

    add_edge(vdA, vdB, g);
    add_edge(vdA, vdC, g);

    pair<adjacency_iterator, adjacency_iterator> p = adjacent_vertices(vdA, g);
    adjacency_iterator                           b = p.first;
    adjacency_iterator                           e = p.second;
    if (b != e) {
        vertex_descriptor vd = *b;
        ASSERT_EQ(vdB, vd);}
    ++b;
    if (b != e) {
        vertex_descriptor vd = *b;
        ASSERT_EQ(vdC, vd);}
    ++b;
    ASSERT_EQ(e, b);
}
