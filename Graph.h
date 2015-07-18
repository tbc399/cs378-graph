// --------------------------
// projects/c++/graph/Graph.h
// Copyright (C) 2015
// Glenn P. Downing
// --------------------------

#ifndef Graph_h
#define Graph_h

// --------
// includes
// --------

#include <cassert> // assert
#include <cstddef> // size_t
#include <utility> // make_pair, pair
#include <vector>  // vector

// -----
// Graph
// -----

class Graph {
    public:
        // --------
        // typedefs
        // --------

        typedef unsigned int vertex_descriptor;  // fix!
        typedef unsigned int edge_descriptor;    // fix!

        typedef unsigned int vertex_iterator;    // fix!
        typedef int* edge_iterator;      // fix!
        typedef unsigned int* adjacency_iterator; // fix!

        typedef std::size_t vertices_size_type;
        typedef std::size_t edges_size_type;

    public:
        // --------
        // add_edge
        // --------

        /**
         * <your documentation>
         */
        friend std::pair<edge_descriptor, bool> add_edge (vertex_descriptor u, 
        												  vertex_descriptor v, 
        												  Graph& g) {
            // <your code>
            
            /*
            pair<map::iterator, bool> p = e.insert(make_pair(++Graph::num_edges, make_pair(u, v)));
            if (!p.second)
            	--Graph::num_edges;
            */

            vertex_size_type n = max(u, v) + 1;
            if (n > g.x.size())
            	g.x.resize(n);

            pair<set::iterator, bool> p = v[u].insert(v);                             //go tot he index u, insert the vertex v there

            if(p.second == true){
                edge_descriptor temp = num_edges++;

                e.insert(make_pair(temp, make_pair(u, v)));
                
                return make_pair(temp, true);
            } else{

                //how to get the edgedescriptor index
                return make_pair(, false);                          //the first needs to be the edgedescriptor index
            }

        }

        // ----------
        // add_vertex
        // ----------

        /**
         * Add a new single vertex to this Graph
         * @param g the Graph to add the vertex to
         * @return a vertex_descriptor for the new vertex
         */
        friend vertex_descriptor add_vertex (Graph& g) {
            g.v.resize(g.v.size() + 1);
            return g.v.size();
        }

        // -----------------
        // adjacent_vertices
        // -----------------

        /**
         * <your documentation>
         */
        friend std::pair<adjacency_iterator, adjacency_iterator> adjacent_vertices (vertex_descriptor, const Graph&) {
            // <your code>
            static int a [] = {0, 0};     // dummy data
            adjacency_iterator b = a;
            adjacency_iterator e = a + 2;
            return std::make_pair(b, e);}

        // ----
        // edge
        // ----

        /**
         * <your documentation>
         */
        friend std::pair<edge_descriptor, bool> edge (vertex_descriptor, vertex_descriptor, const Graph&) {
            // <your code>
            edge_descriptor ed = 0;
            bool            b  = true;
            return std::make_pair(ed, b);}

        // -----
        // edges
        // -----

        /**
         * <your documentation>
         */
        friend std::pair<edge_iterator, edge_iterator> edges (const Graph&) {
            // <your code>
            static int a [] = {0, 0};     // dummy data
            edge_iterator b = a;
            edge_iterator e = a + 2;
            return std::make_pair(b, e);}

        // ---------
        // num_edges
        // ---------

        /**
         * <your documentation>
         */
        friend edges_size_type num_edges (const Graph&) {
            // <your code>
            edges_size_type s = 1; // fix
            return s;}

        // ------------
        // num_vertices
        // ------------

        /**
         * <your documentation>
         */
        friend vertices_size_type num_vertices (const Graph&) {
            // <your code>
            vertices_size_type s = 1; // fix
            return s;}

        // ------
        // source
        // ------

        /**
         * <your documentation>
         */
        friend vertex_descriptor source (edge_descriptor, const Graph&) {
            // <your code>
            vertex_descriptor v = 0; // fix
            return v;}

        // ------
        // target
        // ------

        /**
         * <your documentation>
         */
        friend vertex_descriptor target (edge_descriptor, const Graph&) {
            // <your code>
            vertex_descriptor v = 0; // fix
            return v;}

        // ------
        // vertex
        // ------

        /**
         * <your documentation>
         */
        friend vertex_descriptor vertex (vertices_size_type, const Graph&) {
            // <your code>
            vertex_descriptor vd = 0; // fix
            return vd;}

        // --------
        // vertices
        // --------

        /**
         * <your documentation>
         */
        friend std::pair<vertex_iterator, vertex_iterator> vertices (const Graph&) {
            // <your code>
            static int a [] = {0, 0};     // dummy data
            vertex_iterator b = a;
            vertex_iterator e = a + 2;
            return std::make_pair(b, e);}

    private:
        // ----
        // data
        // ----

        std::vector< std::set<vertex_descriptor> > v; // something like this

		std::map<edge_descriptor, std::pair<vertex_descriptor, vertex_descriptor>> e;  //key is the edge desciptor, the value is a pair of verticies
		
		static unsigned int num_edges; 
		
        // -----
        // valid
        // -----

        /**
         * <your documentation>
         */
        bool valid () const {
            // <your code>
            return true;}

    public:
        // ------------
        // constructors
        // ------------

        /**
         * Construct an empty adjacency list graph
         */
        Graph () {
            // <your code>
            assert(valid());
       	}

        // Default copy, destructor, and copy assignment
        // Graph  (const Graph<T>&);
        // ~Graph ();
        // Graph& operator = (const Graph&);
};

unsigned int Graph::num_edges = 0;

#endif // Graph_h
