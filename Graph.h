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

        typedef unsigned int vertex_descriptor;  // fix! done
        typedef unsigned int edge_descriptor;    // fix! done

        typedef std::vector<vertex_descriptor>::const_iterator vertex_iterator;    // fix! done
        typedef std::vector<edge_descriptor>::const_iterator edge_iterator;      // fix! done
        typedef std::set<vertex_descriptor>::const_iterator adjacency_iterator;

        typedef std::size_t vertices_size_type;
        typedef std::size_t edges_size_type;

    public:
        // --------
        // add_edge
        // --------

        /**
         * Adds an edge, from u -> v, and increases the size
         */
        friend std::pair<edge_descriptor, bool> add_edge (vertex_descriptor u, 
        												  vertex_descriptor v, 
        												  Graph& g) {

			//Do we need to check if they try and add a edge where u == v?
            // <your code>
            vertices_size_type n = max(u, v) + 1;
            if (n > g.v.size()){
		g.vd.resize(n);
            	g.v.resize(n);
	    }

            pair<set<vertex_descriptor>::iterator, bool> p = g.v[u].insert(v); 

            if(p.second){
                edge_descriptor temp = g.num_edges++;
                g.e1.insert(make_pair(temp, make_pair(u, v)));
                g.e2.insert(make_pair(make_pair(u, v), temp));
		        g.ed.push_back(temp);
                return make_pair(temp, true);
            } else {
                return make_pair(g.e2.at(make_pair(u, v)), false);
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
 	        g.vd.push_back(g.vd.size());
            
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
			return std::make_pair(g.e2.at(std::make_pair(u , v)),true);
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
        friend std::pair<edge_iterator, edge_iterator> edges (const Graph& g) {

            edge_iterator edge_it1 = g.ed.begin();
            edge_iterator edge_it2 = g.ed.end();

	       return std::make_pair(edge_it1, edge_it2);}		

        // ---------
        // num_edges
        // ---------

        /**
         * Returns the number of edges in the graph
         */
        //friend edges_size_type num_edges (const Graph&) {
        friend edges_size_type num_edges (const Graph& g) {

            return g.num_edges;}

        // ------------
        // num_vertices
        // ------------

        /**
         * returns the number of vertices
         */
        friend vertices_size_type num_vertices (const Graph& g) {
            
	    return g.vd.size();}

        // ------
        // source
        // ------

        /**
         * returns the source of where the edge starts
         */
        friend vertex_descriptor source (edge_descriptor e, const Graph& g) {

	    try{
		return g.e1.at(e).first;	
	    }
	    catch(std::out_of_range& e){
		return 0;
	    }

        }

        // ------
        // target
        // ------

        /**
         *  
         */
        friend vertex_descriptor target (edge_descriptor e, const Graph& g) {

	    try{
		return g.e1.at(e).second;
	    }
	    catch(std::out_of_range &e){
		return 0;
	    }

            return 0;}

        // ------
        // vertex
        // ------

        /**
         * Passes in the nth vertex. just return n 
         */
        friend vertex_descriptor vertex (vertices_size_type n, const Graph& g) {

            return n;}

        // --------
        // vertices
        // --------

        /**
         * Returns a pair of vertex iterators over vd, graph is const
         */
        friend std::pair<vertex_iterator, vertex_iterator> vertices (const Graph& g) {
            
	       return std::make_pair(g.vd.begin(), g.vd.end());}   

    private:
        // ----
        // data
        // ----

    std::vector< std::set<vertex_descriptor> > v; // something like this

	std::map<edge_descriptor, std::pair<vertex_descriptor, vertex_descriptor>> e1;  //key is the edge desciptor, the value is a pair of verticies
		
    std::map<std::pair<vertex_descriptor, vertex_descriptor>, edge_descriptor> e2;
        
	unsigned int num_edges; 

	std::vector<edge_descriptor> ed;

	std::vector<vertex_descriptor> vd;
		
        // -----
        // valid
        // -----

        /**
         * valid function, to be checked, the # of edges is equal across all the data structures and the # of verices is equal across their data structures 
         */
        bool valid () const {
        
            // cout << e1.size() << endl;
            // cout << e2.size() << endl;
            // cout << num_edges << endl;
            // cout << ed.size() << endl;
            // cout << vd.size() << endl;

            if (e1.size() != e2.size())
                    return false;

            if (e2.size() != num_edges)
                    return false;

            if (num_edges != ed.size())
                    return false;

            if(v.size() != vd.size())
		            return false;
		    
		return true;}

    public:
        // ------------
        // constructors
        // ------------

        /**
         * Construct an empty adjacency list graph
         */
        Graph () {
            num_edges = 0;
            assert(valid());
       	}

        // Default copy, destructor, and copy assignment
        // Graph  (const Graph<T>&);
        // ~Graph ();
        // Graph& operator = (const Graph&);
};

// unsigned int Graph::num_edges = 0;

#endif // Graph_h
