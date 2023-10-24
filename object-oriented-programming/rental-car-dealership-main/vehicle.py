import datetime


class Vehicle:
    def __init__(self, brand, model, plate, daily_rate, factory_year) -> None:
        self.brand = brand
        self.model = model
        self.plate = plate
        self.daily_rate = daily_rate
        self.factory_year = factory_year
        self.date_it_was_rented = "It is available"
        self.date_it_will_be_returned = "It is available"
        self.rented_days = "It is available"
        self.amount = 0.0
    
    def get_brand(self):
        return self.brand
    
    def get_model(self):
        return self.model
    
    def get_plate(self):
        return self.plate

    def get_daily_rate(self):
        return self.daily_rate

    def get_factory_year(self):
        return self.factory_year

    def reset_vehicle_rent_data(self):
        self.date_it_was_rented = "It is available"
        self.date_it_will_be_returned = "It is available"
        self.rented_days = "It is available"
        self.amount = 0.0

    def get_rental_date(self):
        return [self.date_it_was_rented, self.date_it_will_be_returned, self.rented_days]

    # método que só deverá ser manipulado por um objeto rent, ou seja, quando o veiculo for alugado 
    def set_rental_date(self, date_it_was_rented, date_it_will_be_returned):
        self.date_it_was_rented = datetime.date.fromisoformat(date_it_was_rented)
        self.date_it_will_be_returned = datetime.date.fromisoformat(date_it_will_be_returned)
        self.rented_days = (self.date_it_will_be_returned - self.date_it_was_rented).days
        amount = self.rented_days * self.daily_rate
        self.amount = amount + amount * 0.15

    def get_total_value(self):
        return self.amount