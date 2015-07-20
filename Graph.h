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

        typedef unsigned int vertex_descriptor;  // fix! done
        typedef unsigned int edge_descriptor;    // fix! done

        typedef std::vector<vertex_descriptor>::iterator vertex_iterator;    // fix! done
        typedef std::vector<edge_descriptor>::iterator edge_iterator;      // fix! done
        typedef std::set<vertex_descriptor>::iterator adjacency_iterator;

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

			//Do we need to check if they try and add a edge where u == v?
            // <your code>
            vertex_size_type n = max(u, v) + 1;
            if (n > g.x.size()){
		g.vd.resize(n);
            	g.v.resize(n);
	    }

            pair<set::iterator, bool> p = v[u].insert(v); //go tot he index u, insert the vertex v there

            if(p.second){
                edge_descriptor temp = num_edges++;
                e1.insert(make_pair(temp, make_pair(u, v)));
                e2.insert(make_pair(make_pair(u, v), temp));
		ed.push_back(temp);
                return make_pair(temp, true);
            } else {
                return e2.at(make_pair(u, v));
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

			// if they add a vertex, shouldnt it return a vertex descriptor of 
			// g.v.size() - 1? since the index starts at 0. 
			// for example v has 10 vertices, 0-9. adding one makes it 11, 0-10, we should reutrn the vertex descriptopr 10?

		
            g.v.resize(g.v.size() + 1);
 	    g.vd.resize(g.vd.size() + 1);
            return g.v.size() - 1;
        }

        // -----------------
        // adjacent_vertices
        // -----------------

        /**
         * Get a pair of iterators 
         */
        friend std::pair<adjacency_iterator, adjacency_iterator> adjacent_vertices 
                                                (vertex_descriptor u, const Graph& g) {
            return std::make_pair(g.v[u].begin(), g.v[u].end());
        }

        // ----
        // edge
        // ----

        /**
         * Searches for an edge within our map and returns a pair with that edge descriptor and a bool, returns 0,false if not there
         */
        friend std::pair<edge_descriptor, bool> edge (vertex_descriptor u,
                                            vertex_descriptor v, const Graph& g) {
         
		try{
			return std::make_pair(e2.at(std::make_pair(u , v), true));
		}
		catch(std::out_of_range& e){
			return std::make_pair(0, false);
		}

            return std::make_pair(0, false);}

        // -----
        // edges
        // -----

        /**
         * returns a pair of iterators (beginning and end) of our edges tracker ed
         */
        friend std::pair<edge_iterator, edge_iterator> edges (const Graph&) {

	    return std::make_pair(g.ed.begin(), g.ed.end());}		

        // ---------
        // num_edges
        // ---------

        /**
         * Returns the number of edges in the graph
         */
        //friend edges_size_type num_edges (const Graph&) {
        friend edges_size_type num_edges (const Graph&) {

            return num_edges;}

        // ------------
        // num_vertices
        // ------------

        /**
         * returns the number of vertices
         */
        friend vertices_size_type num_vertices (const Graph&) {
            
	    return g.vd.size();}

        // ------
        // source
        // ------

        /**
         * returns the source of where the edge starts
         */
        friend vertex_descriptor source (edge_descriptor, const Graph&) {

	    try{
		return e1.at(edge_descriptor).first;	
	    }
	    catch(std::out_of_range& e){
		return 0;
	    }

            return v;}

        // ------
        // target
        // ------

        /**
         *  
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

	std::map<edge_descriptor, std::pair<vertex_descriptor, vertex_descriptor>> e1;  //key is the edge desciptor, the value is a pair of verticies
		
        std::map<std::pair<vertex_descriptor, vertex_descriptor>, edge_descriptor> e2;
        
	static unsigned int num_edges; 

	std::vector<edge_descriptor> ed;

	std::vector<vertex_descriptor> vd;
		
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
