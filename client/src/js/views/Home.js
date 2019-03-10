import React, { Component } from 'react'
import { connect } from 'react-redux';

class Home extends Component{
    constructor(props){
        super(props)
    }

    render(){
        return(
            <div>
                <h1>Home sweet Home</h1>
            </div>
        )
    }
}

const mapStateToProps = (state) => {
    return {

    }
}

const mapDispatchToProps = (dispatch) => {
    return {

    }
}

export default connect(mapStateToProps, mapDispatchToProps)(Home)