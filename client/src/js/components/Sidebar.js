
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

    calculateRoute(){
       this.props.coreActions.getRouteByCoordinate()
    }

    calculateTime(){
        var timeInMinutes = this.props.pathCost
        var hours = Math.floor(timeInMinutes / 216000)
        var minutes = (timeInMinutes- (hours*216000))/3600
        return hours + " h " + minutes.toFixed(0) + " m"
    }

    render(){
        return(
            <aside> 
            <div>OSM Stuff</div>
            <button onClick={e => this.generateShareLink(e)}>Generate Share Link</button>
            <FilledInput disabled value={this.props.sharelink}/>
            <button onClick={e => this.calculateRoute(e)}>CalculateRoute</button>
            {this.props.pathCost ? <h3>{this.calculateTime()}</h3> : null}
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
        sharelink: state.core.sharelink,
        pathCost : state.map.route.pathCost

    }
};

const mapDispatchToProps = (dispatch) => {
    return {
        coreActions: bindActionCreators(coreActions, dispatch)
    }
};

// We wrap our Sidebar with the Router, and then to the redux store
export default connect(mapStateToProps, mapDispatchToProps)(Sidebar)