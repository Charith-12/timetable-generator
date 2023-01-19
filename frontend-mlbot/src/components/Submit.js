import React, { useState } from 'react'
import axios from 'axios'

// set of functions to get values form local storage

function Submit () {

    // const [batchName,setbatchName] = useState('');
    // const [noStudents,setnoStudents] = useState(0);
    const [batches,setbatches] = useState('');
    const [lecturers,setlecturers] = useState('');
    const [modules,setmodules] = useState('');




const getlocal_batches = () => {
 
    
    if(localStorage.getItem('batches')){
        setbatches(JSON.parse(localStorage.getItem('batches')));
    }

}

const  getlocal_lecturers =() => {
    if(localStorage.getItem('lecturers')){
        setlecturers(JSON.parse(localStorage.getItem('lecturers')))
    }
}

const getlocal_modules =() => {
    if(localStorage.getItem('ModuleInfoArray')){
        setmodules(JSON.parse(localStorage.getItem('ModuleInfoArray')))
    }
}

// set of functions to send to the database

 const  sendto_batches = async () => {

    getlocal_batches();

 let batchName = "";
 let noStudents = 0;
    
    const submiteachBatch = () => {
        try {
        axios.post('http://localhost:3001/api/insert/batches',{
          batch_name: batchName,
          no_students: noStudents,
        }).then(() =>{
          alert("succesful insert");
        });}
        catch(error){
            console.log(error);
        }
    }
        for (let i = 0; i < batches.length; i++){
            let batch = batches[i];
             batchName = batch.name;
             noStudents = batch.numStudents;
             submiteachBatch();
        }


  
     


}

const sendto_lecturers = async () => {
 getlocal_lecturers();

    let lecname = '';
    let lecid = 0;
    let maxHours = 0;
    let payRate = 0;

    const submiteachLecturer = () => {
        try {
        axios.post('http://localhost:3001/api/insert/lecturers',{
          lec_id: lecid,
          lec_name: lecname,
          maxHours: maxHours,
          payRate : payRate,
        }).then(() =>{
          alert("succesful insert to lectr");
        });}
        catch(error){
            console.log(error);
        }
    }

 
        for (let i = 0; i < lecturers.length; i++){
            let lecturer = lecturers[i];
             lecname = lecturer.name;
             lecid = lecturer.lecid;
             maxHours = lecturer.maxHours;
             payRate = lecturer.payRate;
             submiteachLecturer();
        }



}

const  sendto_module = async () => {

    getlocal_modules();

    let modname = '';
    let modecode = 0;
    let credits = 0;

    const submiteachModule = () => {
        try {
        axios.post('http://localhost:3001/api/insert/modules',{
          modename: modname,
          modecode: modecode,
          credits: credits,
        }).then(() =>{
          alert("succesful insert to lectr");
        });}
        catch(error){
            console.log(error);
        }
    }

 
        for (let i = 0; i < modules.length; i++){
            let module = modules[i];
             modname = module.name;
             modecode =  module.code;
             credits =  module.credits;
             submiteachModule();
        }


}

const sendto_lec_modules = async () => {

    let lec_id = ''
    let lecmodules = []
    let module_code = ''
 
    const submiteachLecMod = () => {
     try {
     axios.post('http://localhost:3001/api/insert/lec_modules',{
       lec_id: lec_id,
       module_code: module_code,
     }).then(() =>{
       alert("succesful insert to lec_modules");
     });}
     catch(error){
         console.log(error);
     }
 }
 
    for (let i = 0; i < lecturers.length; i++){
     let lecturer = lecturers[i];
      lec_id = lecturer.lecid;
      lecmodules = lecturer.lecModules;
         for (let j = 0 ; j < lecmodules.length; j++){
             module_code =  lecmodules[j]
             submiteachLecMod();
         }
 }

}

const sendto_batch_modules = async () => {

   let batch_name = ''
   let batchmodules = []
   let module_code = ''

   const submiteachBatchMod = () => {
    try {
    axios.post('http://localhost:3001/api/insert/batch_modules',{
      batchname: batch_name,
      module_code: module_code,
    }).then(() =>{
      alert("succesful insert to batch_modules");
    });}
    catch(error){
        console.log(error);
    }
}

   for (let i = 0; i < batches.length; i++){
    let batch = batches[i];
     batch_name = batch.name;
     batchmodules = batch.modules;
        for (let j = 0 ; j< batchmodules.length; j++){
            module_code =  batchmodules[j]
            submiteachBatchMod();
        }
}


}

const sendto_constraints =  async () => {
let costDay = 0;
let costHours = 0;
let costHire = 0;
let intervalBetweenSlots = 0;

if(localStorage.getItem('costToExtendDays')){
    costDay = localStorage.getItem('costToExtendDays');
}

if(localStorage.getItem('costToExtendHours')){
    costHours = localStorage.getItem('costToExtendHours');
}

if(localStorage.getItem('costToHire')){
    costHire = localStorage.getItem('costToHire');
}

if(localStorage.getItem('intervalBetweenSlots')){
    intervalBetweenSlots = localStorage.getItem('intervalBetweenSlots');
}

const submiteachBatch = () => {
    try {
    axios.post('http://localhost:3001/api/insert/constraints',{
      costToExtendDays: costDay,
      costToExtendHours: costHours,
      costToHire: costHire,
      intervalBetweenSlots: intervalBetweenSlots,
    }).then(() =>{
      alert("succesful insert");
    });}
    catch(error){
        console.log(error);
    }
}


}






// async function SendtoDB  (){
//     console.log("send butoon pressed!")
//     await sendto_batches().then(
//     sendto_module()).then(
//     sendto_lecturers()).then(
//     sendto_batch_modules()).then(
//     sendto_lec_modules()).then(
//         sendto_constraints()
//     ).then(
       
// alert('did this')
//     );
// }


async function SendtoDB() {
    console.log("send butoon pressed!")
    try {
        await sendto_batches();
        await sendto_module();
        await sendto_lecturers();
        await sendto_batch_modules();
        await sendto_lec_modules();
        await sendto_constraints();
        alert("Data sent successfully");
    } catch (error) {
        console.error(error);
        alert("An error occurred while sending the data");
    }
}


    return (
   <button
   onClick={SendtoDB}
   >Submit</button>
  )
}

export default Submit