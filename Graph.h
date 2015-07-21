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

using namespace std;

class Graph {
    public:
        // --------
        // typedefs
        // --------

        typedef unsigned int vertex_descriptor;
        typedef pair<vertex_descriptor, vertex_descriptor> edge_descriptor;

        typedef std::vector<vertex_descriptor>::const_iterator vertex_iterator;
        typedef std::set<edge_descriptor>::const_iterator edge_iterator;
        typedef std::set<vertex_descriptor>::const_iterator adjacency_iterator;

        typedef std::size_t vertices_size_type;
        typedef std::size_t edges_size_type;

    public:
        // --------
        // add_edge
        // --------

        /**
         * Adds an edge, from u -> v, and increases the size
         * @param u the source vertex
         * @param v the target vertex
         * @param g a graph to act on
         * @return a pair with an edge-descriptor and a bool to
         * represent if the edge already exists
         */
        friend std::pair<edge_descriptor, bool> add_edge (vertex_descriptor u, 
        												  vertex_descriptor v, 
        												  Graph& g) {

            vertices_size_type n = max(u, v) + 1;
            if (n > g.v.size()){
                vertices_size_type start = g.vd.size();
                while (start < n) {
                    g.vd.push_back(start);
                    ++start;
                }
            	g.v.resize(n);
            }

            pair<set<vertex_descriptor>::iterator, bool> p = g.v[u].insert(v); 

            if(p.second){
                edge_descriptor temp = make_pair(u, v);
		        g.ed.insert(temp);
                return make_pair(temp, true);
            } else {
                return make_pair(make_pair(u, v), false);
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
 	        g.vd.push_back(g.vd.size());
            return g.v.size() - 1;
        }

        // -----------------
        // adjacent_vertices
        // -----------------

        /**
         * Get a pair of adjacency_iterator to the beginning and end of the set of 
         * vertices that are adjacent to a specified vertex
         * @param u a vertex
         * @param g a graph to act on
         * @return a pair with an adjacency_iterator to the beginning of the 
         * adjacent vertices to u and one to the end of the adjacent vertices
         */
        friend std::pair<adjacency_iterator, adjacency_iterator> adjacent_vertices 
                                                (vertex_descriptor u, const Graph& g) {
            return std::make_pair(g.v[u].begin(), g.v[u].end());
        }

        // ----
        // edge
        // ----

        /**
         * Searches for an edge within our map and returns a pair with that edge
         * descriptor and a bool, returns 0,false if not there
         * @param u a source vertex
         * @param v a target vertex
         * @param g a graph to act on
         * @return a pair with an edge_descriptor and a bool to
         * represent if the edge already exists
         */
        friend std::pair<edge_descriptor, bool> edge (vertex_descriptor u,
                                            vertex_descriptor v, const Graph& g) {
            set<edge_descriptor>::iterator it = find(g.ed.begin(), g.ed.end(), make_pair(u,v));
    		if (it == g.ed.end()) {
                return make_pair(make_pair(u, v), false);
            } else {
                return make_pair(make_pair(u,v), true);
            }
        }

        // -----
        // edges
        // -----

        /**
         * Get a pair of iterators (beginning and end) of our edges tracker
         * @param g a graph to act on
         * return a pair with an edge_iterator to the beginning of the 
         * set of edges in g and one to the end of the set of edges
         */
        friend std::pair<edge_iterator, edge_iterator> edges (const Graph& g) {
            return std::make_pair(g.ed.begin(), g.ed.end());
        }		

        // ---------
        // num_edges
        // ---------

        /**
         * Get the number of edges in the graph
         * @param g a graph to act on
         * @return the number of edges in the graph g
         */
        friend edges_size_type num_edges (const Graph& g) {
            return g.ed.size();
        }

        // ------------
        // num_vertices
        // ------------

        /**
         * Get the number of vertices in the graph
         * @param g a graph to act on
         * @return the number of vertices in the graph g
         */
        friend vertices_size_type num_vertices (const Graph& g) {
            return g.vd.size();
        }

        // ------
        // source
        // ------

        /**
         * Get the source of a specified edge
         * @param e an edge_descriptor
         * @param g a graph to act on
         * @return a vertex_descriptor to the source of e
         */
        friend vertex_descriptor source (edge_descriptor e, const Graph& g) {
    	    return e.first;
        }

        // ------
        // target
        // ------

        /**
         * Get the target of a specified edge
         * @param e an edge_descriptor
         * @param g a graph to act on
         * @return a vertex_descriptor to the target of e
         */
        friend vertex_descriptor target (edge_descriptor e, const Graph& g) {
    	    return e.second;
        }

        // ------
        // vertex
        // ------

        /**
         * Get the vertex at the nth place in the vertices of the graph
         * @param n a vertices_size_type
         * @param g a graph to act on
         * @return a vertex_descriptor of the nth vertex in the graph g 
         */
        friend vertex_descriptor vertex (vertices_size_type n, const Graph& g) {
            return n;
        }

        // --------
        // vertices
        // --------

        /**
         * Returns a pair of vertex_iterator to the beginning and end of the set
         * of vertices in a graph
         * @param g a graph to act on
         * @return a pair with a vertex_iterator to the beginning of the vertices
         * in the graph g and one to the end of the vertices in the graph g
         */
        friend std::pair<vertex_iterator, vertex_iterator> vertices (const Graph& g) {
            return std::make_pair(g.vd.begin(), g.vd.end());
        }   

    private:
        // ----
        // data
        // ----

        std::vector< std::set<vertex_descriptor> > v;

    	std::set<edge_descriptor> ed;

    	std::vector<vertex_descriptor> vd;
		
        // -----
        // valid
        // -----

        bool valid () const {

            if(v.size() != vd.size())
                return false;
		    
            return true;
        }

    public:
        // ------------
        // constructors
        // ------------

        /**
         * Construct an empty adjacency list graph
         */
        Graph () {
            assert(valid());
       	}

        // Default copy, destructor, and copy assignment
        // Graph  (const Graph<T>&);
        // ~Graph ();
        // Graph& operator = (const Graph&);
};
#endif // Graph_h
