package model;


import javafx.collections.FXCollections;
import javafx.collections.ObservableList;

public class SuperMarkets {
    private final ObservableList<SuperMarket> SuperMarkets;

    public SuperMarkets() {
        SuperMarkets = FXCollections.observableArrayList(
                new SuperMarket("John Smith", "john.smith@uts.com", "user222"),
                new SuperMarket("Jane Tyler", "jane.tyler@uts.com", "super123"),
                new SuperMarket("Chao Yang", "t", "t")
        );      
    }
   
    public boolean hasSuperMarket(String name, String password) {
        return SuperMarkets.stream().anyMatch(p -> (p.login(name, password)));
    }
    public boolean hasLogin(String email, String password) {
        return SuperMarkets.stream().anyMatch(p -> (p.login(email, password)));
    }

    public SuperMarket getSuperMarket(String name, String password){
        for(SuperMarket e:SuperMarkets)
            if(e.login(name, password))
                return e;
        return null;
    }
    public String getName(String email, String password){
        for(SuperMarket e:SuperMarkets)
            if(e.login(email, password))
                return e.getName();
        return null;
    }
}


