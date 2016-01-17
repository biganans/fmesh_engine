////////////////////////////////////////////////////////////////////////
//
// This file is part of Common Text Transformation Library.
// Copyright (C) 1997-2009 by Igor Kholodov. 
//
// Common Text Transformation Library is free software: you can
// redistribute it and/or modify it under the terms of the
// GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Common Text Transformation Library is distributed in the hope
// that it will be useful, but WITHOUT ANY WARRANTY; without even
// the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
// PURPOSE.  See the GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with Common Text Transformation Library.
// If not, see <http://www.gnu.org/licenses/>.
//
// mailto:cttl@users.sourceforge.net
// http://cttl.sourceforge.net/
// http://sourceforge.net/projects/cttl/
//
////////////////////////////////////////////////////////////////////////

/**@file xtl_base.h
 * @brief Defines base classes for <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page6200_lexeme.html">lexeme</a> objects.
 *
 * @warning
 *      This is internal CTTL header file and should not
 *      be included by user programs.
 *
 *  @see
 *  - cttl_impl::iswhat_T
 *  - cttl_impl::iswwhat_T
 *  - cttl_impl::xtl_wrap
 *  - cttl_impl::xtl_edge
 *  - cttl_impl::xtl_node
 */

// xtl_base.h

#ifndef _CTTL_XTLBASE_H_INCLUDED_
#define _CTTL_XTLBASE_H_INCLUDED_

#include <cwchar>
#include "coreutils.h"
#include "policy_state.h"

namespace cttl_impl {

    /**Defines type of C character classification routine.*/
    typedef int ( *iswhat_T )( int );

    /**Defines type of C wide character classification routine.*/
    typedef int ( *iswwhat_T )( std::wint_t );

}   // namespace cttl_impl

#include "xtl_trace.h"

namespace cttl_impl {

/**@struct xtl_wrap
 *@brief Wraps C++ types generated by compiler for CTTL grammar expressions.
 *
 * @tparam ExprT
 *        specifies type of
 *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar expression</a>.
 *        The actual type is determined by the C++ compiler at compile time.
 *
 */
template< typename ExprT >
struct xtl_wrap {

    // compile-time

    /**Stores encapsulated <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar expression</a>.*/
    ExprT m_expr;

    /**Default constructor.*/
    xtl_wrap()
    : m_expr( ExprT() )
    {
//      CTTL_TRACE_MESSAGE( CTTL_TRACE_TYPEID( &m_expr ) );
    }

    /**Constructs xtl_wrap object for any type.*/
    template< typename GenericT >
    xtl_wrap( GenericT const& x_ )
    : m_expr( ExprT( x_ ) )
    {
//      CTTL_TRACE_MESSAGE( CTTL_TRACE_TYPEID( &m_expr ) );
    }

    /**Copy constructor.*/
    xtl_wrap( xtl_wrap< ExprT > const& other_ )
    : m_expr( other_.m_expr )
    {
    }

    /**Delegates
    *  grammar <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">evaluation algorithm</a>
    *  call to the encapsulated <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar expression</a>.
    *
    * @tparam SubstrT
    *        specifies type of <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *        Can be either @c cttl::const_edge or @c cttl::edge.
    *
    * @param edge_
    *        reference to parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *
    * @return
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1300_interface.html">result</a> of evaluated <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar expression</a>.
    *
    */
    template< typename SubstrT >
    size_t match( SubstrT& edge_ )
    {
        return m_expr.match( edge_ );
    }

    /**Delegates
    *  grammar <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">evaluation algorithm</a>
    *  call to the encapsulated <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar expression</a>.
    *
    * @tparam SubstrT
    *        specifies type of <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *        Can be either @c cttl::const_edge or @c cttl::edge.
    *
    * @param edge_
    *        reference to parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *
    * @return
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1300_interface.html">result</a> of evaluated <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar expression</a>.
    *
    */
    template< typename SubstrT >
    size_t find( SubstrT& edge_ )
    {
        return m_expr.find( edge_ );
    }

    /**Delegates
    *  grammar <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">evaluation algorithm</a>
    *  call to the encapsulated <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar expression</a>.
    *
    * @tparam SubstrT
    *        specifies type of <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *        Can be either @c cttl::const_edge or @c cttl::edge.
    *
    * @param edge_
    *        reference to parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *
    * @return
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1300_interface.html">result</a> of evaluated <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar expression</a>.
    *
    */
    template< typename SubstrT >
    size_t bang_find( SubstrT& edge_ )
    {
        return m_expr.bang_find( edge_ );
    }

#ifdef CTTL_STATEFUL_RUNTIME_MATCH
    /**Delegates
    *  grammar <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">evaluation algorithm</a>
    *  call to the encapsulated <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar expression</a>.
    *
    * @tparam SubstrT
    *        specifies type of <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *        Can be either @c cttl::const_edge or @c cttl::edge.
    *
    * @param edge_
    *        reference to parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *
    * @return
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1300_interface.html">result</a> of evaluated <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar expression</a>.
    *
    */
    template< typename SubstrT >
    size_t runtime_match( SubstrT& edge_ )
    {
        assert( &edge_.space_policy() != NULL || !"Stateful policy must be provided by the user." );
        if ( edge_.space_policy().m_flags.test( cttl::policy_default::xtl_flag_runtime_bang_find ) ) {
            edge_.space_policy().m_flags.clear( cttl::policy_default::xtl_flag_runtime_bang_find );
            return m_expr.bang_find( edge_ );

        } else if ( edge_.space_policy().m_flags.test( cttl::policy_default::xtl_flag_runtime_find ) ) {
            edge_.space_policy().m_flags.clear( cttl::policy_default::xtl_flag_runtime_find );
            return m_expr.find( edge_ );
        }
        
        return m_expr.match( edge_ );
    }
#endif //CTTL_STATEFUL_RUNTIME_MATCH

    private:
        /**Assignment is disabled.*/
        xtl_wrap< ExprT >& operator=( xtl_wrap< ExprT > const& );

};  // xtl_wrap


/**@class xtl_edge
 * @brief Implements behavior of CTTL
 *        edge <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar expression</a>
 *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page7000_expr.html">adaptor</a>.
 *
 * @tparam EdgeT
 *        specifies CTTL substring
 *        type, either @c cttl::const_edge, or @c cttl::edge
 *        template class.
 *
 * @tparam ExprT
 *        specifies type of
 *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar expression</a>.
 *        The actual type is determined by the C++ compiler at compile time.
 *
 */
template< typename EdgeT, typename ExprT >
class xtl_edge {

private:
    /**Encapsulated substring object.*/
    EdgeT& m_edge;

    /**Encapsulated expression.*/
    ExprT m_expr;

public:
    // compile-time

    /**Constructs and initializes the object.*/
    xtl_edge( EdgeT& edge_, ExprT const& expr_ )
    :
    m_edge( edge_ ),
    m_expr( expr_ )
    {
    }

    // run-time

    /**Delegates
    *  grammar <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">evaluation algorithm</a>
    *  call to the encapsulated <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar expression</a>.
    *
    * @tparam SubstrT
    *        specifies type of <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *        Can be either @c cttl::const_edge or @c cttl::edge.
    *
    * @param edge_
    *        reference to parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *
    * @return
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1300_interface.html">result</a> of evaluated <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar expression</a>.
    *
    * @post
    *        If algorithm succeeds, encapsulated substring is positioned
    *        on the boundaries of the matched fragment. 
    *
    */
    template< typename SubstrT >
    size_t match( SubstrT& edge_ )
    {
        CTTL_TRACE_LEVEL_MATCH( 'e' );
        CTTL_TRACE_JUSTIFY();
        CTTL_TRACE_NODE_IDENTITY( m_edge.first.identity( edge_.first ) );
        CTTL_TRACE_NODE_IDENTITY( m_edge.second.identity( edge_.first ) );
        CTTL_TRACE_NODE_IDENTITY( 0 );
        size_t match_offset = m_expr.match( edge_ );
        if ( match_offset != SubstrT::string_T::npos ) {
            m_edge.first.offset( match_offset );
            m_edge.second.offset( edge_.first.offset() );
            CTTL_TRACE_EDGE_RESULT_TRUE( 'e' );
            return match_offset;
        }

        CTTL_TRACE_EDGE_RESULT_FALSE( 'e', m_edge.first.identity( edge_.first ) );
        return SubstrT::string_T::npos;
    }
    
    /**Delegates
    *  grammar <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">evaluation algorithm</a>
    *  call to the encapsulated <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar expression</a>.
    *
    * @tparam SubstrT
    *        specifies type of <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *        Can be either @c cttl::const_edge or @c cttl::edge.
    *
    * @param edge_
    *        reference to parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *
    * @return
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1300_interface.html">result</a> of evaluated <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar expression</a>.
    *
    * @post
    *        If algorithm succeeds, encapsulated substring is positioned
    *        on the boundaries of the matched fragment. 
    *
    */
    template< typename SubstrT >
    size_t find( SubstrT& edge_ )
    {
        CTTL_TRACE_LEVEL_FIND( 'e' );
        CTTL_TRACE_JUSTIFY();
        CTTL_TRACE_NODE_IDENTITY( m_edge.first.identity( edge_.first ) );
        CTTL_TRACE_NODE_IDENTITY( m_edge.second.identity( edge_.first ) );
        CTTL_TRACE_NODE_IDENTITY( 0 );
        size_t match_offset = m_expr.find( edge_ );
        if ( match_offset != SubstrT::string_T::npos ) {
            m_edge.first.offset( match_offset );
            m_edge.second.offset( edge_.first.offset() );
            CTTL_TRACE_EDGE_RESULT_TRUE( 'e' );
            return match_offset;
        }

        CTTL_TRACE_EDGE_RESULT_FALSE( 'e', m_edge.first.identity( edge_.first ) );
        return SubstrT::string_T::npos;
    }
    
    /**Delegates
    *  grammar <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">evaluation algorithm</a>
    *  call to the encapsulated <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar expression</a>.
    *
    * @tparam SubstrT
    *        specifies type of <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *        Can be either @c cttl::const_edge or @c cttl::edge.
    *
    * @param edge_
    *        reference to parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *
    * @return
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1300_interface.html">result</a> of evaluated <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar expression</a>.
    *
    * @post
    *        If algorithm succeeds, encapsulated substring is positioned
    *        on the boundaries of the matched fragment. 
    *
    */
    template< typename SubstrT >
    size_t bang_find( SubstrT& edge_ )
    {
        CTTL_TRACE_LEVEL_BANG( 'e' );
        CTTL_TRACE_JUSTIFY();
        CTTL_TRACE_NODE_IDENTITY( m_edge.first.identity( edge_.first ) );
        CTTL_TRACE_NODE_IDENTITY( m_edge.second.identity( edge_.first ) );
        CTTL_TRACE_NODE_IDENTITY( 0 );
        size_t match_offset = m_expr.bang_find( edge_ );
        if ( match_offset != SubstrT::string_T::npos ) {
            m_edge.first.offset( match_offset );
            m_edge.second.offset( edge_.first.offset() );
            CTTL_TRACE_EDGE_RESULT_TRUE( 'e' );
            return match_offset;
        }

        CTTL_TRACE_EDGE_RESULT_FALSE( 'e', m_edge.first.identity( edge_.first ) );
        return SubstrT::string_T::npos;
    }
    
    private:
        /**Assignment is disabled.*/
        xtl_edge< EdgeT, ExprT >& operator=( xtl_edge< EdgeT, ExprT > const& );

};  // xtl_edge


/**@class xtl_node
 * @brief Implements behavior of CTTL
 *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page7010_node.html">node expression adaptor</a>.
 *
 * @tparam NodeT
 *        specifies @c cttl::node.
 *
 * @tparam ExprT
 *        specifies type of
 *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar expression</a>.
 *        The actual type is determined by the C++ compiler at compile time.
 *
 */
template< typename NodeT, typename ExprT >
class xtl_node {

private:
    /**Encapsulated node object.*/
    NodeT& m_node;

    /**Encapsulated expression.*/
    ExprT m_expr;

public:
    // compile-time

    /**Constructs and initializes the object.*/
    xtl_node( NodeT& node_, ExprT const& expr_ )
    :
    m_node( node_ ),
    m_expr( expr_ )
    {
    }

    // run-time

    /**Delegates
    *  grammar <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">evaluation algorithm</a>
    *  call to the encapsulated <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar expression</a>.
    *
    * @tparam SubstrT
    *        specifies type of <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *        Can be either @c cttl::const_edge or @c cttl::edge.
    *
    * @param edge_
    *        reference to parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *
    * @return
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1300_interface.html">result</a> of evaluated <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar expression</a>.
    *
    * @post
    *        If algorithm succeeds, encapsulated node is positioned
    *        on the upper boundary of the matched fragment. 
    *
    */
    template< typename SubstrT >
    size_t match( SubstrT& edge_ )
    {
        typedef typename SubstrT::strict_edge_T strict_universe_T;

        CTTL_TRACE_LEVEL_MATCH( 'n' );
        CTTL_TRACE_JUSTIFY();
        CTTL_TRACE_NODE_IDENTITY( m_node.identity( edge_.first ) );
        CTTL_TRACE_NODE_IDENTITY( 0 );
        size_t match_offset = m_expr.match( edge_ );
        if ( match_offset != SubstrT::string_T::npos ) {
            m_node.offset( match_offset );
            // strict_universe_T needed, otherwise a custom policy
            // would have to have a default constructor:
            CTTL_TRACE_NODE_RESULT_TRUE( 'n', strict_universe_T( m_node, edge_.first ) );
            return match_offset;
        }

        CTTL_TRACE_NODE_RESULT_FALSE( 'n', m_node.identity( edge_.first ) );
        return SubstrT::string_T::npos;
    }
    
    /**Delegates
    *  grammar <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">evaluation algorithm</a>
    *  call to the encapsulated <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar expression</a>.
    *
    * @tparam SubstrT
    *        specifies type of <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *        Can be either @c cttl::const_edge or @c cttl::edge.
    *
    * @param edge_
    *        reference to parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *
    * @return
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1300_interface.html">result</a> of evaluated <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar expression</a>.
    *
    * @post
    *        If algorithm succeeds, encapsulated node is positioned
    *        on the upper boundary of the matched fragment. 
    *
    */
    template< typename SubstrT >
    size_t find( SubstrT& edge_ )
    {
        typedef typename SubstrT::strict_edge_T strict_universe_T;

        CTTL_TRACE_LEVEL_FIND( 'n' );
        CTTL_TRACE_JUSTIFY();
        CTTL_TRACE_NODE_IDENTITY( m_node.identity( edge_.first ) );
        CTTL_TRACE_NODE_IDENTITY( 0 );
        size_t match_offset = m_expr.find( edge_ );
        if ( match_offset != SubstrT::string_T::npos ) {
            m_node.offset( match_offset );
            // strict_universe_T needed, otherwise a custom policy
            // would have to have a default constructor:
            CTTL_TRACE_NODE_RESULT_TRUE( 'n', strict_universe_T( m_node, edge_.first ) );
            return match_offset;
        }

        CTTL_TRACE_NODE_RESULT_FALSE( 'n', m_node.identity( edge_.first ) );
        return SubstrT::string_T::npos;
    }
    
    /**Delegates
    *  grammar <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">evaluation algorithm</a>
    *  call to the encapsulated <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar expression</a>.
    *
    * @tparam SubstrT
    *        specifies type of <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *        Can be either @c cttl::const_edge or @c cttl::edge.
    *
    * @param edge_
    *        reference to parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *
    * @return
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1300_interface.html">result</a> of evaluated <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar expression</a>.
    *
    * @post
    *        If algorithm succeeds, encapsulated node is positioned
    *        on the upper boundary of the matched fragment. 
    *
    */
    template< typename SubstrT >
    size_t bang_find( SubstrT& edge_ )
    {
        typedef typename SubstrT::strict_edge_T strict_universe_T;

        CTTL_TRACE_LEVEL_BANG( 'n' );
        CTTL_TRACE_JUSTIFY();
        CTTL_TRACE_NODE_IDENTITY( m_node.identity( edge_.first ) );
        CTTL_TRACE_NODE_IDENTITY( 0 );
        size_t match_offset = m_expr.bang_find( edge_ );
        if ( match_offset != SubstrT::string_T::npos ) {
            m_node.offset( match_offset );
            // strict_universe_T needed, otherwise a custom policy
            // would have to have a default constructor:
            CTTL_TRACE_NODE_RESULT_TRUE( 'n', strict_universe_T( m_node, edge_.first ) );
            return match_offset;
        }

        CTTL_TRACE_NODE_RESULT_FALSE( 'n', m_node.identity( edge_.first ) );
        return SubstrT::string_T::npos;
    }
    
    private:
        /**Assignment is disabled.*/
        xtl_node< NodeT, ExprT >& operator=( xtl_node< NodeT, ExprT > const& );

};  // xtl_node


}   // namespace cttl_impl

#endif // _CTTL_XTLBASE_H_INCLUDED_
