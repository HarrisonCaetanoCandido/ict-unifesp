from exceptions import VehicleCurrentlyRentedError, YouHaveAlreadyRentedThisVehicle


class Rent:
    def __init__(self, user):
        self.renter = user
        self.rented_vehicle = []

    def add_vehicle(self, vehicle, date_it_was_rented, date_it_will_be_returned):
        if self.search_an_already_rented_vehicle(vehicle) is not None:
            raise YouHaveAlreadyRentedThisVehicle

        if vehicle.get_rental_date() != ['It is available', 'It is available', 'It is available']:
            raise VehicleCurrentlyRentedError

        vehicle.set_rental_date(date_it_was_rented, date_it_will_be_returned)
        self.rented_vehicle.append(vehicle)

    def remove_vehicle(self, plate):
        for index in range(0, len(self.rented_vehicle)):
            if self.rented_vehicle[index].plate == plate:
                self.rented_vehicle[index].reset_vehicle_rent_data()
                del (self.rented_vehicle[index])
                return

    def get_rented_vehicles(self):
        return [self.rented_vehicle, len(self.rented_vehicle)]

    def search_an_already_rented_vehicle(self, vehicle):
        for item in self.rented_vehicle:
            if item == vehicle:
                return item
