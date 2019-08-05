
import React, { PropTypes } from 'react'
import { connect } from 'react-redux'
import { bindActionCreators } from 'redux'

import FilledInput from '@material-ui/core/FilledInput'
import { makeStyles } from '@material-ui/core/styles';

import * as coreActions from '../services/core/actions'


class Sidebar extends React.Component{

    constructor(props){
        super(props);
    }

    generateShareLink(){
       this.props.coreActions.generateShareLink()
    }

    render(){
        return(
            <aside> 
            <div>OSM Stuff</div>
            <button onClick={e => this.generateShareLink(e)}>Generate Share Link</button>
            <FilledInput disabled value={this.props.sharelink}/>
            </aside>
        )
    }
}


/**
 * Export our component
 *
 * We also integrate our global store, using connect()
 **/

const mapStateToProps = (state, ownProps) => {
    return {
        sharelink: state.core.sharelink

    }
};

const mapDispatchToProps = (dispatch) => {
    return {
        coreActions: bindActionCreators(coreActions, dispatch)
    }
};

// We wrap our Sidebar with the Router, and then to the redux store
export default connect(mapStateToProps, mapDispatchToProps)(Sidebar)