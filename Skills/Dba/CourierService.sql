--
-- PostgreSQL database dump
--

-- Dumped from database version 14.2 (Ubuntu 14.2-1.pgdg20.04+1)
-- Dumped by pg_dump version 14.2 (Ubuntu 14.2-1.pgdg20.04+1)

SET statement_timeout = 0;
SET lock_timeout = 0;
SET idle_in_transaction_session_timeout = 0;
SET client_encoding = 'UTF8';
SET standard_conforming_strings = on;
SELECT pg_catalog.set_config('search_path', '', false);
SET check_function_bodies = false;
SET xmloption = content;
SET client_min_messages = warning;
SET row_security = off;

SET default_tablespace = '';

SET default_table_access_method = heap;

--
-- Name: employees; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.employees (
    id integer NOT NULL,
    manager_id integer,
    full_name character varying,
    address character varying,
    phone character varying,
    hired_at timestamp without time zone,
    fired_at timestamp without time zone
);


ALTER TABLE public.employees OWNER TO postgres;

--
-- Name: employees_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public.employees_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.employees_id_seq OWNER TO postgres;

--
-- Name: employees_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public.employees_id_seq OWNED BY public.employees.id;


--
-- Name: order_states; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.order_states (
    id integer NOT NULL,
    state character varying
);


ALTER TABLE public.order_states OWNER TO postgres;

--
-- Name: order_states_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public.order_states_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.order_states_id_seq OWNER TO postgres;

--
-- Name: order_states_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public.order_states_id_seq OWNED BY public.order_states.id;


--
-- Name: orders; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.orders (
    id integer NOT NULL,
    customer character varying,
    address character varying,
    courier_id integer,
    price numeric
);


ALTER TABLE public.orders OWNER TO postgres;

--
-- Name: orders_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public.orders_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.orders_id_seq OWNER TO postgres;

--
-- Name: orders_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public.orders_id_seq OWNED BY public.orders.id;


--
-- Name: trace; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.trace (
    id bigint NOT NULL,
    state_id integer,
    order_id integer,
    updated_at timestamp without time zone
);


ALTER TABLE public.trace OWNER TO postgres;

--
-- Name: trace_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public.trace_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.trace_id_seq OWNER TO postgres;

--
-- Name: trace_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public.trace_id_seq OWNED BY public.trace.id;


--
-- Name: employees id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.employees ALTER COLUMN id SET DEFAULT nextval('public.employees_id_seq'::regclass);


--
-- Name: order_states id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.order_states ALTER COLUMN id SET DEFAULT nextval('public.order_states_id_seq'::regclass);


--
-- Name: orders id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.orders ALTER COLUMN id SET DEFAULT nextval('public.orders_id_seq'::regclass);


--
-- Name: trace id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.trace ALTER COLUMN id SET DEFAULT nextval('public.trace_id_seq'::regclass);


--
-- Data for Name: employees; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.employees (id, manager_id, full_name, address, phone, hired_at, fired_at) FROM stdin;
1	1	Иванов Иван Иванович	Невский проспект, 11	+790865454	2022-05-04 12:10:57	2022-05-06 13:10:57
2	2	Иванова Анна Ивановна	Набережная реки Мойки, 48	+790865454	2022-05-04 12:10:57	2022-05-06 13:10:57
\.


--
-- Data for Name: order_states; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.order_states (id, state) FROM stdin;
1	новый
2	в доставке
3	доставлен
4	отменен
\.


--
-- Data for Name: orders; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.orders (id, customer, address, courier_id, price) FROM stdin;
1	Иванов Алесандр Иванович	Баумана, 121	2	150
2	Иванов Андрей Иванович	Ленина, 122	2	200
3	Иванов Михаил Иванович	Ленина, 122	1	150
\.


--
-- Data for Name: trace; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.trace (id, state_id, order_id, updated_at) FROM stdin;
1	4	3	2022-06-06 13:20:57
2	2	2	2022-07-07 13:20:58
3	3	1	2022-05-05 14:02:07
4	4	3	2022-06-06 13:20:57
5	4	3	2022-07-05 13:25:28
6	1	3	2022-06-05 14:01:07
\.


--
-- Name: employees_id_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public.employees_id_seq', 2, true);


--
-- Name: order_states_id_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public.order_states_id_seq', 4, true);


--
-- Name: orders_id_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public.orders_id_seq', 3, true);


--
-- Name: trace_id_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public.trace_id_seq', 6, true);


--
-- Name: employees employees_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.employees
    ADD CONSTRAINT employees_pkey PRIMARY KEY (id);


--
-- Name: order_states order_states_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.order_states
    ADD CONSTRAINT order_states_pkey PRIMARY KEY (id);


--
-- Name: orders orders_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.orders
    ADD CONSTRAINT orders_pkey PRIMARY KEY (id);


--
-- Name: trace trace_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.trace
    ADD CONSTRAINT trace_pkey PRIMARY KEY (id);


--
-- Name: employees employees_manager_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.employees
    ADD CONSTRAINT employees_manager_id_fkey FOREIGN KEY (manager_id) REFERENCES public.employees(id);


--
-- Name: orders orders_courier_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.orders
    ADD CONSTRAINT orders_courier_id_fkey FOREIGN KEY (courier_id) REFERENCES public.employees(id);


--
-- Name: trace trace_order_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.trace
    ADD CONSTRAINT trace_order_id_fkey FOREIGN KEY (order_id) REFERENCES public.orders(id);


--
-- Name: trace trace_state_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.trace
    ADD CONSTRAINT trace_state_id_fkey FOREIGN KEY (state_id) REFERENCES public.order_states(id);


--
-- PostgreSQL database dump complete
--

