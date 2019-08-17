
import React, { PropTypes } from 'react'
import { connect } from 'react-redux'
import { bindActionCreators } from 'redux'

import { FontAwesomeIcon } from '@fortawesome/react-fontawesome'
import { faAngleLeft } from '@fortawesome/free-solid-svg-icons'
import { withStyles } from '@material-ui/core/styles';
import Button from '@material-ui/core/Button';
import TextField from '@material-ui/core/TextField';


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
                <div className="liner">
                    <div className="brand">OSM HOWLONG</div>
                    <div>
                        {this.props.sharelink? 
                            <TextField
                            id="filled-read-only-input"
                            label="sharelink"
                            defaultValue={this.props.sharelink}
                            className="sharedfield"
                            margin="normal"
                            InputProps={{
                                readOnly: true,
                            }}
                            variant="filled"
                        /> :    
                        <Button onClick={e => this.generateShareLink(e) }  className = "button-action" variant="contained" >
                        Generate Share Link
                        </Button>
                        }  
                    </div>
                    <div>
                        {this.props.calculationTime? 
                            <TextField
                            id="filled-read-only-input"
                            label="Algorithmtime in seconds"
                            value={(this.props.calculationTime/1000000).toFixed(2)}
                            className="sharedfield"
                            margin="normal"
                            InputProps={{
                                readOnly: true,
                            }}
                            variant="filled"
                        /> : null}  
                    </div>

                </div>
                <div className="close" onClick={e => this.props.coreActions.toggleSidebar(false)}>
                    <FontAwesomeIcon icon={faAngleLeft} size="2x"></FontAwesomeIcon>
                </div>
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
        pathCost : state.map.route.pathCost,
        calculationTime : state.map.route.timeForSearch

    }
};

const mapDispatchToProps = (dispatch) => {
    return {
        coreActions: bindActionCreators(coreActions, dispatch)
    }
};

// We wrap our Sidebar with the Router, and then to the redux store
export default connect(mapStateToProps, mapDispatchToProps)(Sidebar)