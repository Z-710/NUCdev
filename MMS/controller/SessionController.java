package controller;

import au.edu.uts.ap.javafx.Controller;
import au.edu.uts.ap.javafx.ViewLoader;
import java.io.*;
import javafx.beans.property.*;
import java.io.File;
import java.io.FileInputStream;
import javafx.event.*;
import javafx.event.ActionEvent;
import javafx.fxml.*;
import javafx.scene.control.Label;
import javafx.scene.control.TableView;
import javafx.scene.control.*;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.stage.*;
import model.*;
import javafx.application.Application;



public class SessionController extends Controller<SuperMarkets>{    
    SuperMarkets superMarkets = new SuperMarkets();
    public final SuperMarkets getSuperMarkets(){return superMarkets;}
    private Image img = new Image("view/loGo.png"); 
    private ImageView view = new ImageView(img);
    @FXML private Label logo;
    @FXML private TextField email;
    @FXML private TextField password;
    @FXML private Label incorrect;
    @FXML private Label title;
    
    @FXML private void initialize() { 
           view.setPreserveRatio(true);
           view.setFitHeight(400);
           view.setFitWidth(500);
           try{
              logo.setGraphic(view);  
           }
           catch(Exception e){}
               
    }
    
    @FXML private void handleLogin(ActionEvent event) throws Exception {
            Stage login = new Stage();
            login.getIcons().add(new Image("view/book.png"));
            login.setX(ViewLoader.X);
            login.setY(ViewLoader.Y);
            login.centerOnScreen();
            ViewLoader.showStage(getSuperMarkets(),"/view/Login.fxml", "Sign in", login);
            
        }
    @FXML private void handleExit(ActionEvent event) throws Exception {
        stage.close();
        }
    public final String getEmail(){
        return email.getText();
    }
    public final String getPassword(){
        return password.getText();
    }
    private final void incorrect(String text){
        incorrect.setText(""+ text);
    }
    
    @FXML private void handleLoginCheck(ActionEvent event) throws Exception {   
            if (superMarkets.hasLogin(getEmail(),getPassword())){
                Stage supermarket = new Stage();
                supermarket.getIcons().add(new Image("view/SuperMarket.png"));
                supermarket.setX(ViewLoader.X);
                supermarket.setY(ViewLoader.Y);
                supermarket.centerOnScreen();
                stage.close();
                String password = getPassword();
                String name = superMarkets.getName(getEmail(),password);
                //System.out.println(name +"  "+ password);
                ViewLoader.showStage(superMarkets.getSuperMarket(getEmail(),password),"/view/SuperMarket.fxml", "Session Admin: " + superMarkets.getName(getEmail(),password) , supermarket);
            }
            else{
                incorrect("incorrect login details");
            }
            
        }
}

