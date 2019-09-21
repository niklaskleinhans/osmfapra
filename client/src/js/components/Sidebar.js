
import React, { PropTypes } from 'react'
import { connect } from 'react-redux'
import { bindActionCreators } from 'redux'

import { FontAwesomeIcon } from '@fortawesome/react-fontawesome'
import { faAngleLeft } from '@fortawesome/free-solid-svg-icons'

import Button from '@material-ui/core/Button';
import TextField from '@material-ui/core/TextField';
import FormControl from '@material-ui/core/FormControl';
import Radio from '@material-ui/core/Radio';
import RadioGroup from '@material-ui/core/RadioGroup';
import FormControlLabel from '@material-ui/core/FormControlLabel';
import FormLabel from '@material-ui/core/FormLabel';

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

    changeAlgorithm(event){
        this.props.coreActions.setAlgorithm(event.target.value)
    }

    changeEpsilonDistancePath(event){
        if(parseInt(event.target.value)){
            this.props.coreActions.changeEpsilonDistancePath(parseInt(event.target.value))
        }
    }
    
    changeEpsilonDistanceMax(event){
        if(parseInt(event.target.value)){
            this.props.coreActions.changeEpsilonDistanceMax(parseInt(event.target.value))
        }
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
                            margin="dense"
                            InputProps={{
                                readOnly: true,
                            }}
                            variant="filled"
                        /> : null}  
                    </div>

                </div>
                <div className="bottom-button">
                        <hr></hr>
                    {this.props.routeConfig.epsilonDistancePath?
                        <TextField
                            id="filled-read-only-input"
                            label="Epsilon Path Distance"
                            defaultValue={this.props.routeConfig.epsilonDistancePath}
                            onChange={e => this.changeEpsilonDistancePath(e)}
                            className="configinput"
                            margin="dense"
                            variant="filled"
                            type="Number"
                        />: null 
                    
                    }

                    {this.props.routeConfig.epsilonDistanceMax?
                        <TextField
                            id="filled-read-only-input"
                            label="Max Update Distance"
                            defaultValue={this.props.routeConfig.epsilonDistanceMax}
                            onChange={e => this.changeEpsilonDistanceMax(e)}
                            className="configinput"
                            margin="dense"
                            variant="filled"
                            type="Number"
                        />: null
                    }
                    <hr></hr>
                    <FormControl component="fieldset">
                        <FormLabel style={{color:"#efe1d6"}}>Select Algorithm</FormLabel>
                        <hr></hr>
                        <RadioGroup aria-label="gender" name="gender1" value={this.props.algorithm} onChange={e => this.changeAlgorithm(e)}>
                            <FormControlLabel value="dijkstra" control={<Radio style={{color:"#a7bfb4"}}/>} label="Dijkstra" />
                            <FormControlLabel value="bidirectionaldijkstra" control={<Radio style={{color:"#a7bfb4"}} />} label="Bidirectional Dijkstra" />
                        </RadioGroup>
                    </FormControl>
                        <hr></hr>
                    <Button onClick={e => this.props.coreActions.toggleServerinfo() }  className = "button-info" variant="contained" >
                    Show Server Info
                    </Button>
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
        routeConfig: state.core.config,
        pathCost : state.map.route.pathCost,
        calculationTime : state.map.route.timeForSearch,
        algorithm : state.core.algorithm

    }
};

const mapDispatchToProps = (dispatch) => {
    return {
        coreActions: bindActionCreators(coreActions, dispatch)
    }
};

// We wrap our Sidebar with the Router, and then to the redux store
export default connect(mapStateToProps, mapDispatchToProps)(Sidebar)