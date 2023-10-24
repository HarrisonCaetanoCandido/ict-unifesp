from vehicle import Vehicle
from signup import SignUp
from signin import SignIn
from inmemoryuserrepository import InMemoryUserRepository
from exceptions import UserEmailAlreadyRegistered, IncorrectEmailOrPassword, InvalidPasswordError
import pytest


def test_sign_up_password_length_verification():
    user_repo = InMemoryUserRepository('harrison', 'hA44yZ0n_')
    sign_up = SignUp(user_repo)

    # less than 6 characters
    with pytest.raises(InvalidPasswordError):
        sign_up.perform('Harrison Caetano Cândido', 'h.candido20@unifesp.br', 'A13&7')

    # more than 12 characters
    with pytest.raises(InvalidPasswordError):
        sign_up.perform('Harrison Caetano Cândido', 'h.candido20@unifesp.br', '0000000A013&7')


def test_sign_up_password_alfabetic_verification():
    user_repo = InMemoryUserRepository('harrison', 'hA44yZ0n_')
    sign_up = SignUp(user_repo)

    # upper_letters
    with pytest.raises(InvalidPasswordError):
        sign_up.perform('Harrison Caetano Cândido', 'h.candido20@unifesp.br', '0aa13&7')

    # lower_letters
    with pytest.raises(InvalidPasswordError):
        sign_up.perform('Harrison Caetano Cândido', 'h.candido20@unifesp.br', '0AA13&7')


def test_sign_up_password_special_character_verification():
    user_repo = InMemoryUserRepository('harrison', 'hA44yZ0n_')
    sign_up = SignUp(user_repo)

    with pytest.raises(InvalidPasswordError):
        sign_up.perform('Harrison Caetano Cândido', 'h.candido20@unifesp.br', '0Aa13777')


def test_sign_up_user():
    user_repo = InMemoryUserRepository('harrison', 'hA44yZ0n_')
    sign_up = SignUp(user_repo)
    sign_up.perform('Harrison Caetano Cândido', 'h.candido20@unifesp.br', 'Aa12345&7')

    assert user_repo.find_by_email('h.candido20@unifesp.br') is not None


def test_sign_up_user_email_already_registered():
    user_repo = InMemoryUserRepository('harrison', 'hA44yZ0n_')
    sign_up = SignUp(user_repo)
    sign_up.perform('Harrison Caetano Cândido', 'h.candido20@unifesp.br', 'Aa12345&7')

    with pytest.raises(UserEmailAlreadyRegistered):
        sign_up.perform('Harrison Caetano Cândido', 'h.candido20@unifesp.br', 'Aa12345&7')


def test_sign_in_user():
    user_repo = InMemoryUserRepository('harrison', 'hA44yZ0n_')
    sign_up = SignUp(user_repo)
    sign_up.perform('Harrison Caetano Cândido', 'h.candido20@unifesp.br', 'Aa12345&7')

    sign_in = SignIn(user_repo)

    # aqui ele deve retornar o objeto usuário logado
    assert sign_in.perform('h.candido20@unifesp.br', 'Aa12345&7') is not False


def test_sign_in_wrong_password():
    user_repo = InMemoryUserRepository('harrison', 'hA44yZ0n_')
    sign_up = SignUp(user_repo)
    sign_up.perform('Harrison Caetano Cândido', 'h.candido20@unifesp.br', 'Aa12345&7')

    sign_in = SignIn(user_repo)

    # aqui deve ser lancada uma excessao para email nao encontrado
    with pytest.raises(IncorrectEmailOrPassword):
        sign_in.perform('h.candido27@unifesp.br', 'Aa12345&7')

    # aqui deve ser lancada uma excessao para senha nao encontrada
    with pytest.raises(IncorrectEmailOrPassword):
        sign_in.perform('h.candido20@unifesp.br', '121345&7')


def test_rent_a_vehicle():
    user_repo = InMemoryUserRepository('harrison', 'hA44yZ0n_')

    sign_up = SignUp(user_repo)
    sign_up.perform('Harrison Caetano Cândido', 'h.candido20@unifesp.br', 'Aa12345&7')

    sign_in = SignIn(user_repo)
    user = sign_in.perform('h.candido20@unifesp.br', 'Aa12345&7')

    car_a = Vehicle('Dodge', 'Challenger SRT Hellcat', 'xlsx4267', 10.75, 2019)
    car_b = Vehicle('Chevrolet', 'Corvette C8 Stingray', 'csv22347', 10.775, 2022)
    car_c = Vehicle('Ford', 'Mustang Shelby GT500', 'xls332247', 10.777, 2021)

    user.rent_list.add_vehicle(car_a, '2022-11-05', '2022-11-08')
    user.rent_list.add_vehicle(car_b, '2022-11-05', '2022-11-09')
    user.rent_list.add_vehicle(car_c, '2022-11-05', '2022-11-10')

    assert user.rent_list.get_rented_vehicles() == [[car_a, car_b, car_c], 3]

    user.rent_list.remove_vehicle('csv22347')
    assert user.rent_list.get_rented_vehicles() == [[car_a, car_c], 2]
    assert car_b.get_rental_date() == ['It is available', 'It is available', 'It is available']

    user.rent_list.remove_vehicle('xls332247')
    assert user.rent_list.get_rented_vehicles() == [[car_a], 1]
    assert car_c.get_rental_date() == ['It is available', 'It is available', 'It is available']

    user.rent_list.remove_vehicle('xlsx4267')
    assert user.rent_list.get_rented_vehicles() == [[], 0]
    assert car_a.get_rental_date() == ['It is available', 'It is available', 'It is available']


def test_user_self_delete():
    user_repo = InMemoryUserRepository('harrison', 'hA44yZ0n_')
    sign_up = SignUp(user_repo)
    sign_up.perform('Harrison', 'h.candido20@unifesp.br', 'Aa12345&7')

    sign_in = SignIn(user_repo)
    user = sign_in.perform('h.candido20@unifesp.br', 'Aa12345&7')

    user.delete_account('Aa12345&7')

    assert user_repo.find_by_email('h.candido20@unifesp.br') is None
    assert user_repo.get_users_quantity() == 0


def test_delete_user_from_user_repo():
    user_repo = InMemoryUserRepository('harrison', 'hA44yZ0n_')
    sign_up = SignUp(user_repo)
    sign_up.perform('Harrison', 'h.candido20@unifesp.br', 'Aa12345&7')

    user = user_repo.find_by_email('h.candido20@unifesp.br')

    """
    como usamos hash nas senhas, é necessário um método interno para um administrador do banco de usuários
    que possa excluir contas sem precisar crackear a senha, caso esse que seria muito custoso e provavelmente não
    funcionaria para senhas muito fortes
    """

    assert user_repo.remove_user(user.email, 'harrison', 'hA44yZ0n_') == 'This account has been removed'
    assert user_repo.find_by_email('h.candido20@unifesp.br') is None
    assert user_repo.get_users_quantity() == 0
