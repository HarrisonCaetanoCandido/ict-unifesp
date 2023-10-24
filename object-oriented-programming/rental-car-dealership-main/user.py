from rent import Rent


class User:
    def __init__(self, name, email, password, user_repo):
        self.name = name
        self.email = email
        self.password = password
        self.rent_list = Rent(self)
        """
        this attribute is useful when users want to delete their own account, 
        so we are going to set them user_repo address
        """
        self.__user_repo_address = user_repo  # private attribute

    def get_name(self):
        return self.name

    def get_email(self):
        return self.email

    def get_password(self):
        return self.password

    def reset_password(self, password):
        self.password = password

    def get_rent_list(self):
        return self.rent_list

    # useful method when users want to self-delete their account
    def delete_account(self, password):
        self.__user_repo_address.delete_account(self.email, password)
