/**
 * @file   Edge.h
 * @brief  An object to define a "edge" which is used to connect
 *         space points in a triangulation algorithm.
 * @author Tracy Usher (usher@slac.stanford.edu)
 * @see    Edge.cxx
 * 
 */

#ifndef LARDATAOBJ_RECOBASE_EDGE_H
#define LARDATAOBJ_RECOBASE_EDGE_H


// C/C++ libraries
#include <cstddef> // std::size_t
#include <iosfwd>

namespace recob
{
    /**
     * @brief Edge is an object containing the results of a Principal Components
     *        Analysis of a group of space points.
     */
    class Edge
    {
    public:
    
        Edge();
    
    private:
    
        double       fLength;           ///< Length of this Edge
        size_t       fFirstPointID;     ///< ID of the SpacePoint edge emanates from
        size_t       fSecondPointID;    ///< ID of the SpacePoint edge ends on
        size_t       fID;               ///< Edge ID
    
    public:
    
        Edge(const double length, size_t firstPointID, size_t secondPointID, size_t id=0);
    
        double              getLength()        const;
        size_t              getFirstPointID()  const;
        size_t              getSecondPointID() const;
        size_t              getID()            const;
    
        friend std::ostream&  operator << (std::ostream & o, const Edge& a);
        friend bool operator < (const Edge& a, const Edge& b);
    
    }; // class Edge
    
} // namespace recob


inline double  recob::Edge::getLength()        const {return fLength;}
inline size_t  recob::Edge::getFirstPointID()  const {return fFirstPointID;}
inline size_t  recob::Edge::getSecondPointID() const {return fSecondPointID;}
inline size_t  recob::Edge::getID()            const {return fID;}



#endif // LARDATAOBJ_RECOBASE_EDGE_H
