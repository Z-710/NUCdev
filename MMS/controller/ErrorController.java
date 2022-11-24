package controller;

import au.edu.uts.ap.javafx.Controller;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.Label;
import javafx.scene.control.ListView;
import javafx.scene.layout.VBox;

public class ErrorController extends Controller<Validator> {
    public Validator getValidator(){return model;}
    @FXML VBox errors;  
    @FXML private void initialize() {
        errors.setSpacing(-10);
        for(String error: getValidator().errors()){
            Label errorlbl = new Label();
            errors.getChildren().add(errorlbl);
            errorlbl.setText(error);
        }
    }
    
    
    
    @FXML private void handleClose(ActionEvent event) throws Exception {
        errors.getChildren().clear();
        getValidator().clear();
        stage.close();
        }


}
