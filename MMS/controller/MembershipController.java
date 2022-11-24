package controller;

import au.edu.uts.ap.javafx.Controller;
import au.edu.uts.ap.javafx.ViewLoader;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.TextField;
import javafx.scene.image.Image;
import javafx.stage.Stage;
import javafx.stage.WindowEvent;
import model.MMS;
import model.Membership;


public class MembershipController extends Controller<Membership> {
    public  Membership getMembership(){return model;}
    Validator validator = new Validator();
    @FXML private TextField Name;
    @FXML private TextField Email;
    @FXML private TextField Phone;
    @FXML private TextField Address;
    @FXML private TextField ID;
    @FXML private TextField Expense;
    @FXML private Label type;
    @FXML private Button AddButton;
    @FXML private Button UpdateButton;
    
    @FXML private void initialize() {
        Double expense = getMembership().getexpense();
        String exp = Double.toString(expense); 
        if (getMembership().getName().equals("")){
            UpdateButton.setDisable(true);
        }
        else{AddButton.setDisable(true);}
        Name.setText(getMembership().getName());
        Email.setText(getMembership().getEmail());
        Phone.setText(getMembership().getPhone());
        Address.setText(getMembership().getAddress());
        ID.setText(getMembership().getID());
        Expense.setText(exp);
        type.setText(getMembership().getType());
        
    }
    
    @FXML private void handleClose(ActionEvent event) throws Exception {        
        stage.close();   
        }
    @FXML private void handleUpdate(ActionEvent event) throws Exception {
        String expense = Expense.getText();
        Double exp = Double.valueOf(expense);
        validator.generateErrors(Name.getText().trim(), Email.getText().trim(),Phone.getText().trim(),Address.getText().trim(),ID.getText().trim(),exp);
        Stage Error = new Stage();
        if (!validator.errors().isEmpty()){
        Error.getIcons().add(new Image("view/error.png"));
        Error.setX(ViewLoader.X);
        Error.setY(ViewLoader.Y);
        Error.centerOnScreen();
        ViewLoader.showStage(validator,"/view/error.fxml", "Input Exceptions", Error); 
        }
        else
        {
          getMembership().updateDetails(Name.getText(),Email.getText(),Phone.getText(),Address.getText(),ID.getText(),exp) ;
          stage.close();  
        }   
    
        }
    //@FXML private void handleAdd(ActionEvent event) throws Exception {
        //String expense = Expense.getText();
        //Double exp = Double.valueOf(expense);
        //getMembership().updateDetails(Name.getText(),Email.getText(),Phone.getText(),Address.getText(),ID.getText(),exp) ;
        //getMembership().addMembership(Name.getText(),Email.getText(),Phone.getText(),Address.getText(),ID.getText(),exp);
        //stage.close();
        //}

}
