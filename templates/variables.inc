{% set ssh_allow_scopes = [] -%}
{%- for elt in ssh_allow %}
  {% if elt in hostvars %}
  {# this is a node #}
    {% for addr in hostvars[elt]['ansible_all_ipv4_addresses'] %}
      {%- set _ = ssh_allow_scopes.append(addr) -%}
    {% endfor %}
  {% elif elt|ipaddr %}
  {# this is an IP #}
    {%- set _ = ssh_allow_scopes.append(elt) -%}
  {% else %}
  {# this is a group #}
    {% for hst in groups[elt] %}
      {% for addr in hostvars[hst]['ansible_all_ipv4_addresses'] %}
        {%- set _ = ssh_allow_scopes.append(addr) -%}
      {% endfor %}
    {% endfor %}
  {% endif %}
{% endfor -%}
