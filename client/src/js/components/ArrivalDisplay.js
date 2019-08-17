import React, { PropTypes } from 'react'
import { connect } from 'react-redux'

class ArrivalDisplay extends React.Component{
    constructor(props){
        super(props)
    }

    calculateTime(){
        var timeInMinutes = this.props.pathCost
        var hours = Math.floor(timeInMinutes / 216000)
        var minutes = (timeInMinutes- (hours*216000))/3600
        return hours + " h " + minutes.toFixed(0) + " m"
    }


    render(){
        return(
            this.props.calculationTime?
            <div className={this.props.sidebar_open? "arrival-display-wrapper sidebar-open" : "arrival-display-wrapper" } >
                <div className={this.props.sidebar_open ? " arrival-display sidebar-open": " arrival-display" }>
                    Time needed to Arrive<div className= "time-text">{this.calculateTime()}</div>
                </div>
            </div>:null
        )
    }
}

const mapStateToProps = (state, ownProps) => {
    return {
        calculationTime : state.map.route.timeForSearch,
        pathCost : state.map.route.pathCost,
        sidebar_open : state.core.sidebar_open

    }
}

const mapDispatchToProps = (dispatch) => {
    return {

    }
}

export default connect(mapStateToProps, mapDispatchToProps)(ArrivalDisplay)