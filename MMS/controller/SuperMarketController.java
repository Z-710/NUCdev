package controller;

import au.edu.uts.ap.javafx.Controller;
import au.edu.uts.ap.javafx.ViewLoader;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.TableView;
import javafx.stage.Stage;
import model.*;
import javafx.collections.*;
import javafx.event.*;
import javafx.fxml.*;
import javafx.scene.text.*;
import javafx.scene.control.*;
import javafx.stage.*;
import javafx.beans.property.*;
import java.io.*;
import au.edu.uts.ap.javafx.*;
import java.util.ArrayList;
import java.util.List;
import javafx.beans.value.ChangeListener;
import javafx.scene.image.Image;



public class SuperMarketController extends Controller<SuperMarket>  {
    @FXML private TableView<Membership> membershipsTv;
    public  SuperMarket getSuperMarket(){return model;}
    private ObservableList<Membership> getMembershipsList(){return getSuperMarket().getMemberships();}
    private void FilterList(String name, String email){ getSuperMarket().filterList(name,email);}
    private Membership getMembership(){return membershipsTv.getSelectionModel().getSelectedItem();}
    @FXML private TextField namefilter;
    @FXML private TextField emailfilter;
    @FXML private Button deleteButton;
    @FXML private Button selectButton;
    @FXML private Button SLIPButton;

    
    @FXML private void initialize() {
        deleteButton.setDisable(true);
        selectButton.setDisable(true);
        SLIPButton.setDisable(true);
        membershipsTv.setItems(getMembershipsList());
        namefilter.textProperty().addListener((observable, oldValue, newValue) -> {
        filtername();
        });
        emailfilter.textProperty().addListener((observable, oldValue, newValue) -> {
        filteremail();
        });
        membershipsTv.getSelectionModel().selectedItemProperty().addListener((observable, oldValue, selected) -> {
        deleteButton.setDisable(selected == null);
        selectButton.setDisable(selected == null);
        SLIPButton.setDisable(selected == null);
        });
            
        for(Membership member: getMembershipsList()){
            if(member.getName().equals("")){
                getSuperMarket().removeMembership(member);
            }
        }
        
    }
    @FXML private void handleClose(ActionEvent event) throws Exception {
        stage.close();
        
        }
    @FXML private void handleDelete(ActionEvent event) throws Exception {
        getSuperMarket().removeMembership(getMembership());
        }
    @FXML private void handleSLIP(ActionEvent event) throws Exception {
        Stage membership = new Stage();
        membership.getIcons().add(new Image("view/edit.png"));
        membership.setX(ViewLoader.X);
        membership.setY(ViewLoader.Y);
        membership.centerOnScreen();
        ViewLoader.showStage(getMembership(),"/view/slip.fxml", getMembership().getName()+" Slip Report", membership);
        }
    @FXML private void handleReport(ActionEvent event) throws Exception {
        MMS mms = new MMS(getSuperMarket());
        Stage Mms = new Stage();
        Mms.getIcons().add(new Image("view/uts.jpeg"));
        Mms.setX(ViewLoader.X);
        Mms.setY(ViewLoader.Y);
        Mms.centerOnScreen();
        ViewLoader.showStage(mms,"/view/mms.fxml", "MMS Report", Mms);
        
        }
    @FXML private String getName(){
        return namefilter.getText();
    }
    @FXML private String getEmail(){
        return emailfilter.getText();
    }
            
    @FXML private void filtername(){
        FilterList(getName(),"/all");
        membershipsTv.setItems(getMembershipsList());

    }
    @FXML private void filteremail(){
        FilterList("/all",getEmail());
        membershipsTv.setItems(getMembershipsList());

    }
    @FXML private void handleAdd(ActionEvent event) throws Exception {
        Stage membershipadd = new Stage();
        membershipadd.getIcons().add(new Image("view/edit.png"));
        membershipadd.setX(ViewLoader.X);
        membershipadd.setY(ViewLoader.Y);
        membershipadd.centerOnScreen();
        Membership newmember = new Membership("","","","","",0.0);
        getSuperMarket().addMembership(newmember);
        ViewLoader.showStage(newmember,"/view/Membership.fxml", "Adding New Membership", membershipadd);
        }
    @FXML private void handleSelect(ActionEvent event) throws Exception {
        Stage membership = new Stage();
        membership.getIcons().add(new Image("view/edit.png"));
        membership.setX(ViewLoader.X);
        membership.setY(ViewLoader.Y);
        membership.centerOnScreen();
        ViewLoader.showStage(getMembership(),"/view/Membership.fxml", "Accessing File: " + getMembership().getName(), membership);
        }
}
