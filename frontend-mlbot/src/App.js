
// import { useState } from "react";
import { useState } from "react";
// import DateAdder from "./components/DateAdder";
import Inputer from "./components/Inputer";
// CSS Modules, react-datepicker-cssmodules.css// 







function App() {

  const[showInput,setShowInput] = useState(0)

  const[showNextButton,setShowNextButton] = useState(false)

  function handleUpdateShowNextButton(showNextButton) {
    if (showNextButton === false) {
      setShowNextButton(true);
    } else {
      setShowNextButton(false);
    }
    
  }
  







 

  function handleNext() {
    console.log('Button CLicked');
    setShowInput(showInput + 1);
  }


  function handleBack(){
    console.log("back clicked");
    setShowInput(showInput -1);
  }
  
   
  return (
    // <Provider store={store}>
    <div className="App">
        <header className="header">
          
        <h1>MLBOTGen</h1>
        <h3>The Machine Learning based timetable genrator</h3>
        </header>
        
       {/* <div className="dates">

        <div className="datesForm">
          <h3>Opening Date</h3>
          <DatePicker 
           selected={startDate} 
           onChange={(date) => setStartDate(date)} 
/>  
        </div>
        <div className="datesForm">
          <h3>Closing Date</h3>
          <DatePicker 
           selected={endDate} 
           onChange={(date) => setEndDate(date)} 
/>  
        </div>
        </div> */}
       <Inputer input = {showInput} onUpdateShowNextButton={handleUpdateShowNextButton} goNext = {handleNext}></Inputer>

       <></>

       { showNextButton ?  <></>: 
       
       <div className="NavButton">




       {(showInput === 9) ?  <></>: <button 
        className="button"
        onClick={ handleNext} 
        
 >Next</button>}
     {showInput !== 0 ? <button
      className="button"
      onClick={handleBack}
     > Back</button> : <></>}
     
       </div>
      
      
      
      }

     
       
      
        
       


      </div>
    //  {/* </Provider> */}
   
  );

     }
export default App;
