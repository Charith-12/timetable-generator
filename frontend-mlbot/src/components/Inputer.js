// import { useState } from "react";
import DateAdder from "./DateAdder";

import React from 'react'
import Holidays from "./Holidays";
import Batches from "./Batches";
import Modules from "./Modules";
import Lecturers from "./Lecturers";
// import Timetable from "./Timetable";
import TimeForm from "./TimeForm";
import Submit from "./Submit";
import CostForm from "./costsForm";
import Timetable from "./Timetable";



function Inputer  (props)  {

  function handleUpdateShowNextButton(showNextButton) {
    props.onUpdateShowNextButton(showNextButton);
  }

  function goNext(){
    props.goNext();
  }

    if(props.input ===0){
  return (
    <DateAdder></DateAdder>
  )}
  else if(props.input === 1){
   return(
   <Holidays></Holidays>
    )}
  else if(props.input === 2){
    return (
<Batches></Batches>)}
  else if(props.input === 3){
    return(
      <Modules  onUpdateShowNextButton={handleUpdateShowNextButton}  goNextfunc = {goNext} />
    )}
  else if(props.input === 4 ){
    return (
      <Lecturers></Lecturers>
    )}
    else if(props.input === 5 ){
      return(
        <TimeForm></TimeForm>
      )}
    else if (props.input ===6) {
      return(
        <CostForm></CostForm>
      )
    }
    else if (props.input ===7) {
      return(
        <Submit></Submit>
      )
    }
     else if (props.input ===8) {
      return(
        <Timetable></Timetable>
      )
    }


}

export default Inputer