from user import User
from vehicle import Vehicle
from exceptions import YouHaveAlreadyRentedThisVehicle, VehicleCurrentlyRentedError
import datetime
import pytest


def test_user_getters_setters():
    user = User('Harrison', 'h.candido20@unifesp.br', 'Aa12345&7', None)

    assert user.get_name() == 'Harrison'
    assert user.get_email() == 'h.candido20@unifesp.br'
    assert user.get_password() == 'Aa12345&7'

    user.reset_password('1234577')

    assert user.get_password() == '1234577'


def test_vehicle_getters_setters():
    car = Vehicle('Dodge', 'Challenger SRT Hellcat', 'xlsx4267', 10.75, 2019)

    assert car.get_brand() == 'Dodge'
    assert car.get_model() == 'Challenger SRT Hellcat'
    assert car.get_plate() == 'xlsx4267'
    assert car.get_daily_rate() == 10.75
    assert car.get_rental_date() == ['It is available', 'It is available', 'It is available']
    assert car.get_factory_year() == 2019

    car.set_rental_date('2022-11-05', '2022-11-08')
    assert car.get_rental_date() == [datetime.date.fromisoformat('2022-11-05'),
                                     datetime.date.fromisoformat('2022-11-08'), 3]
    assert car.get_total_value() == 37.0875


def test_rent_getters_setters():
    user = User('Harrison', 'h.candido20@unifesp.br', 'Aa12345&7', None)
    car = Vehicle('Dodge', 'Challenger SRT Hellcat', 'xlsx4267', 10.75, 2019)
    user.rent_list.add_vehicle(car, '2022-11-05', '2022-11-08')

    assert user.rent_list.get_rented_vehicles() == [[car], 1]

    user.rent_list.remove_vehicle(car.plate)

    assert user.rent_list.get_rented_vehicles() == [[], 0]


def test_rent_a_vehicle_already_rented_by_myself():
    user = User('Harrison', 'h.candido20@unifesp.br', 'Aa12345&7', None)
    car = Vehicle('Dodge', 'Challenger SRT Hellcat', 'xlsx4267', 10.75, 2019)
    user.rent_list.add_vehicle(car, '2022-11-05', '2022-11-08')

    with pytest.raises(YouHaveAlreadyRentedThisVehicle):
        user.rent_list.add_vehicle(car, '2022-11-05', '2022-11-09')


def test_rent_a_vehicle_already_rented_by_someone():
    user_a = User('Harrison', 'h.candido20@unifesp.br', 'Aa12345&7', None)
    car = Vehicle('Dodge', 'Challenger SRT Hellcat', 'xlsx4267', 10.75, 2019)
    user_b = User('João', 'joao16@gmail.com', 'Aa123456&7', None)

    user_a.rent_list.add_vehicle(car, '2022-11-05', '2022-11-09')

    with pytest.raises(VehicleCurrentlyRentedError):
        user_b.rent_list.add_vehicle(car, '2022-11-05', '2022-11-09')
